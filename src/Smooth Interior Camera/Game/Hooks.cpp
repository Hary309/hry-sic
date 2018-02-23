/*
*********************************************************************
* File			: Hooks.cpp
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#include "Hooks.h"

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <jitasm.h>

#include "Memory\Hooking.Patterns.h"
#include "Memory\MemMgr.h"
#include "Mod\Mod.h"
#include "Mod\Camera.h"
#include "Mod\Config.h"
#include "Game\prism.h"
#include "Common.h"

namespace Hooks
{
	Mod* g_pMod;

	void CameraEvent(prism::Camera *pGameCam)
	{
		if (!pGameCam)
			return;

		auto pCam = g_pMod->GetCamera();
		pCam->UpdateGameCamera(pGameCam);

		if (!g_pMod->IsPlaying() || !g_pMod->IsActive()) // default
		{
			pGameCam->m_rx = pGameCam->m_rx_predef;
			pGameCam->m_ry = pGameCam->m_ry_predef;
			pGameCam->m_keyboardEv = false;
		}
		else if (g_pMod->IsConfigurating())
		{
			if (pGameCam->m_keyboardEv)
			{
				for (short i = 0; i < 6; ++i)
				{
					if (floatEquals(pGameCam->m_rx_predef, Config::Get()->GetDefaultValue((Config::CameraPos)i)))
					{
						g_pMod->Log(SCS_LOG_TYPE_message, "New value for [%d] %f is %f", i, Config::Get()->m_interiorCamPos[i], pGameCam->m_rx);
						Config::Get()->m_interiorCamPos[i] = pGameCam->m_rx;
						g_pMod->DisableConfigurating();
						Config::Get()->Save();
					}
				}

				pGameCam->m_keyboardEv = false;
			}
		}
		else if (g_pMod->IsActive())
		{
			if (pGameCam->m_keyboardEv)
			{
				float rx = pGameCam->m_rx_predef;

				for (short i = 0; i < 6; ++i)
				{
					if (floatEquals(pGameCam->m_rx_predef, Config::Get()->GetDefaultValue((Config::CameraPos)i)))
					{
						rx = Config::Get()->GetValue((Config::CameraPos)i);

#ifdef TESTING
						std::cout << "New value for '" << pGameCam->m_rx_predef << "' is '" << rx << "'\n";
#endif

						break;
					}
				}

				pCam->UpdateRX(pGameCam->m_rx);
				pCam->MoveTo(rx);

				pGameCam->m_keyboardEv = false;
			}
		}
	}

	struct : jitasm::Frontend
	{
		uintptr_t callAddr;

		void InternalMain() override
		{
			push(rax);
			push(rcx);
			push(rdx);
			push(r8);

			{
				mov(rax, callAddr);
				call(rax);
			}

			pop(r8);
			pop(rdx);
			pop(rcx);
			pop(rax);

			add(rsp, 0x38);
			ret();
		}
	} Asm_CameraEvent;

	uintptr_t CameraEvent_addr;
	uint8_t CameraEvent_pattern[] = { 0x8B, 0x81, 0xB0, 0x02, 0x00, 0x00, 0x89, 0x81, 0x48, 0x03, 0x00, 0x00, 0x8B, 0x81, 0xB4, 0x02, 0x00, 0x00, 0x89, 0x81, 0x4C, 0x03, 0x00, 0x00, 0xC7, 0x81, 0xAC, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	bool Hook_CameraEvent()
	{
		std::stringstream patternStr; 

		for (int i = 0; i < sizeof(CameraEvent_pattern); ++i)
		{
			patternStr << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(CameraEvent_pattern[i]) << " ";
		}

		auto pattern = hook::pattern(patternStr.str().c_str());

		if (pattern.size() > 0)
		{
			CameraEvent_addr = reinterpret_cast<uintptr_t>(pattern.count(1).get(0).get<void>(0));

#ifdef TESTING
			std::cout << "CameraEvent addr: " << std::hex << CameraEvent_addr << "\n";
#endif

			Asm_CameraEvent.callAddr = (uintptr_t)CameraEvent;
			MemMgr::LongJmpHook(CameraEvent_addr, (uintptr_t)Asm_CameraEvent.GetCode());

			return true;
		}
		else
		{
			Mod::Get()->Log(SCS_LOG_TYPE_error, "Data structure is incorrect!");
#ifdef TESTING
			std::cout << "Hook for CameraEvent not found!\n";
#endif
			return false;
		}
	}

	bool Init()
	{
#ifdef  TESTING
		std::cout << "Initializing hooks...\n";
#endif 

		bool inited = true;

		if (!Hook_CameraEvent())
			inited = false;

#ifdef TESTING
		if (inited)
			std::cout << "Hooks initialized!\n";
#endif

		g_pMod = Mod::Get();

		return inited;
	}

	void Unhook()
	{
		if (CameraEvent_addr != 0)
		{
#ifdef TESTING
			std::cout << "Unhooking...\n";
#endif

			memcpy((uint8_t*)CameraEvent_addr, CameraEvent_pattern, sizeof(CameraEvent_pattern));
		}
	}
}