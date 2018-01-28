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
#include <cstdio>

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
						printf("New value for %f is %f\n", pGameCam->m_rx_predef, rx);
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

	bool Hook_CameraEvent()
	{
		auto pattern = hook::pattern("8B  81 B0 02 00 00 89 81 48  03 00 00 8B 81 B4 02 00  00 89 81 4C 03 00 00 C7  81 AC 02 00 00 00 00 00  00");

		if (pattern.size() > 0)
		{
			auto pFunc = pattern.count(1).get(0).get<void>(0);

			Asm_CameraEvent.callAddr = (uintptr_t)CameraEvent;
			MemMgr::LongJmpHook((uintptr_t)pFunc, (uintptr_t)Asm_CameraEvent.GetCode());

			return true;
		}
		else
		{
			Mod::Get()->Log(SCS_LOG_TYPE_error, "Data structure is incorrect!");
#ifdef TESTING
			printf("Hook for CameraEvent not found!\n");
#endif
			return false;
		}
	}

	bool Init()
	{
		bool inited = true;

		if (!Hook_CameraEvent())
			inited = false;

#ifdef TESTING
		if (inited)
			printf("Hooks initialized!\n");
#endif

		g_pMod = Mod::Get();

		return inited;
	}
}