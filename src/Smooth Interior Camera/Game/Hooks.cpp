/** @file Hooks.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "Hooks.hpp"

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Memory/Hooking.Patterns.hpp"
#include "Memory/MemMgr.hpp"
#include "Mod/Mod.hpp"
#include "Mod/Camera.hpp"
#include "Mod/Config.hpp"
#include "Game/prism.hpp"
#include "Common.hpp"
#include "Version.hpp"

namespace Hooks
{
	Mod* g_pMod;

	std::uint16_t gameCamOffset = 0;
	std::uint16_t gameCamPosOffset = 0;

	void __cdecl CameraEvent(uintptr_t gameCamAddr)
	{
		auto pGameCam = reinterpret_cast<prism::InteriorCamera*>(gameCamAddr + gameCamOffset);
		auto pGameCamPos = reinterpret_cast<prism::InteriorCameraPos*>(gameCamAddr + gameCamPosOffset);

		auto pCam = g_pMod->GetCamera();
		pCam->UpdateGameCamera(pGameCamPos);

		if (!g_pMod->IsPlaying() || !g_pMod->IsActive()) // default
		{
			pGameCamPos->m_rx = pGameCam->m_rxEnd;
			pGameCamPos->m_ry = pGameCam->m_ryEnd;
			pGameCam->m_keyboardEv = false;
		}
		else if (g_pMod->IsConfiguring())
		{
			if (pGameCam->m_keyboardEv)
			{
				for (short i = 0; i < 6; ++i)
				{
					if (floatEquals(pGameCam->m_rxEnd, Config::Get()->GetDefaultValue((Config::InteriorCameraPos)i)))
					{
						g_pMod->Log(SCS_LOG_TYPE_message, "New value for [%d] %f is %f", i, Config::Get()->m_interiorCamPos[i], pGameCamPos->m_rx);
						Config::Get()->m_interiorCamPos[i] = pGameCamPos->m_rx;
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
				float rx = pGameCam->m_rxEnd;

				for (short i = 0; i < 6; ++i)
				{
					if (floatEquals(pGameCam->m_rxEnd, Config::Get()->GetDefaultValue((Config::InteriorCameraPos)i)))
					{
						rx = Config::Get()->GetValue((Config::InteriorCameraPos)i);

					#ifdef TESTING
						std::cout << "New value for '" << pGameCam->m_rxEnd << "' is '" << rx << "'\n";
					#endif

						break;
					}
				}

				pCam->UpdateRX(pGameCamPos->m_rx);
				pCam->MoveTo(rx);

				pGameCam->m_keyboardEv = false;
			}
		}
	}

	uintptr_t CameraEvent_addr;

	auto CameraEvent_pattern = "8B 81 ?? ?? 00 00 89 81 ?? ?? 00 00 8B 81 ?? ?? 00 00 89 81 ?? ?? 00 00 C7 81 ?? ?? 00 00 00 00 00 00";

	uint8_t baseBytes[34] = { 0 };

#if defined(X64)

	extern "C"
	{
		uintptr_t CameraEvent_Address = 0;
		uintptr_t CameraEvent_RetnAddress = 0;
		void Asm_CameraEvent();
	}

#elif defined(X86)

	uintptr_t CameraEvent_Address = 0;
	uintptr_t CameraEvent_RetnAddress = 0;

	void __declspec(naked) Asm_CameraEvent()
	{
		__asm 
		{
			pushad
				call CameraEvent_Address
			popad

			jmp CameraEvent_RetnAddress
		}
	}

#endif

	bool Hook_CameraEvent()
	{
		auto pattern = hook::pattern(CameraEvent_pattern);

		if (pattern.size() > 0)
		{
			CameraEvent_addr = reinterpret_cast<uintptr_t>(pattern.count(1).get(0).get<void>(0));

		#ifdef TESTING
			std::cout << "CameraEvent addr: " << std::hex << CameraEvent_addr << "\n";
		#endif

			gameCamOffset = *reinterpret_cast<std::uint16_t*>(CameraEvent_addr + 2) - 4;
			gameCamPosOffset = *reinterpret_cast<std::uint16_t*>(CameraEvent_addr + 8);

		#ifdef TESTING 
			printf("Offsets: %i %i\n", gameCamOffset, gameCamPosOffset);
			printf("Number of bytes to backup: %lld\n", sizeof(baseBytes));
		#endif 
			// backup bytes
			for (int i = 0; i < sizeof(baseBytes); ++i)
			{
				baseBytes[i] = *reinterpret_cast<std::uint8_t*>(CameraEvent_addr + i);
			}

			MemMgr::UnprotectMemory(CameraEvent_addr, sizeof(baseBytes));

			CameraEvent_Address = reinterpret_cast<uintptr_t>(CameraEvent);
			CameraEvent_RetnAddress = CameraEvent_addr + sizeof(baseBytes);
			MemMgr::JmpHook(CameraEvent_addr, (uintptr_t)Asm_CameraEvent);

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
	#ifdef TESTING
		std::cout << "Initializing hooks...\n";
	#endif 

		if (!Hook_CameraEvent())
			return false;

	#ifdef TESTING
		std::cout << "Hooks initialized!\n";
	#endif

		g_pMod = Mod::Get();

		return true;
	}

	void Unhook()
	{
		if (CameraEvent_addr != 0)
		{
#ifdef TESTING
			std::cout << "Unhooking...\n";
#endif

			// restore bytes
			for (int i = 0; i < sizeof(baseBytes); ++i)
			{
				*reinterpret_cast<std::uint8_t*>(CameraEvent_addr + i) = baseBytes[i];
			}
		}
	}
}
