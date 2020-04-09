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

	void __fastcall CameraEvent(uintptr_t gameCamAddr)
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
						g_pMod->Log(SCS_LOG_TYPE_message, "New value for [", i ,"] ", Config::Get()->m_interiorCamPos[i], " is ", pGameCamPos->m_rx);
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


	uint8_t baseBytes[35] = { 0 };

#if defined(X64)

	auto CameraEvent_pattern_V1 = "8B 81 ?? ?? 00 00 89 81 ?? ?? 00 00 8B 81 ?? ?? 00 00 89 81 ?? ?? 00 00 C7 81 ?? ?? 00 00 00 00 00 00";
	auto CameraEvent_pattern_V2 = "F3 0F 10 97 ?? ?? 00 00  F3 0F 10 B7 ?? ?? 00 00  83 F8 01  75 ??  F3 0F 11 97 ?? ?? 00 00  F3 0F 11 B7 ?? ?? 00 00  89 9F ?? ?? 00 00 E9 ?? ?? 00 00";
	extern "C"
	{
		uintptr_t CameraEvent_CallAddress = 0;
		uintptr_t CameraEvent_RetnAddress = 0;
		void Asm_CameraEvent_V1();
		void Asm_CameraEvent_V2();
	}

#elif defined(X86)

	auto CameraEvent_pattern_V1 = "8B 81 ?? ?? 00 00 89 81 ?? ?? 00 00 8B 81 ?? ?? 00 00 89 81 ?? ?? 00 00 C7 81 ?? ?? 00 00 00 00 00 00 8B";
	auto CameraEvent_pattern_V2 = "F3 0F 10 9F ?? ?? 00 00  F3 0F 10 97 ?? ?? 00 00  83 F8 01  75 ??  F3 0F 11 9F ?? ?? 00 00  F3 0F 11 97 ?? ?? 00 00 E9 ?? ?? 00 00";
	uintptr_t CameraEvent_CallAddress = 0;
	uintptr_t CameraEvent_RetnAddress = 0;

	void __declspec(naked) Asm_CameraEvent_V1()
	{
		__asm 
		{
			pushad
				call CameraEvent_CallAddress
			popad

			jmp CameraEvent_RetnAddress
		}
	}

	void __declspec(naked) Asm_CameraEvent_V2()
	{
		__asm
		{
			pushad
				mov ecx, edi
				call CameraEvent_CallAddress
			popad

			jmp CameraEvent_RetnAddress
		}
	}

#endif
	// Temporary code. Just quick fix, I will rewrite it later

	// ETS2: 1.27 - 1.36 ATS: 1.6 - 1.36
	bool Hook_V1()
	{
#ifdef TESTING
		printf("Trying HOOK V1...\n");
#endif

		auto pattern = hook::pattern(CameraEvent_pattern_V1);

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

			CameraEvent_CallAddress = reinterpret_cast<uintptr_t>(CameraEvent);
			CameraEvent_RetnAddress = CameraEvent_addr + 34;
			MemMgr::JmpHook(CameraEvent_addr, (uintptr_t)Asm_CameraEvent_V1);

#ifdef TESTING
			printf("HOOK V1 activated\n");
#endif

			return true;
		}

#ifdef TESTING
		printf("HOOK V1 don't work\n");
#endif

		return false;
	}

	// ETS2: 1.37+, ATS 1.37+
	bool Hook_V2()
	{
#ifdef TESTING
		printf("Trying HOOK V2...\n");
#endif

		auto pattern = hook::pattern(CameraEvent_pattern_V2);

		if (pattern.size() > 0)
		{
			uintptr_t data_addr = reinterpret_cast<uintptr_t>(pattern.count(1).get(0).get<uintptr_t>(0));
			CameraEvent_addr = data_addr + 21;

#ifdef TESTING
			std::cout << "CameraEvent addr: " << std::hex << CameraEvent_addr << "\n";
#endif

			gameCamOffset = *reinterpret_cast<std::uint16_t*>(data_addr + 4) - 4;
			gameCamPosOffset = *reinterpret_cast<std::uint16_t*>(CameraEvent_addr + 4);

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

			CameraEvent_CallAddress = reinterpret_cast<uintptr_t>(CameraEvent);
			CameraEvent_RetnAddress = CameraEvent_addr + 16;
			MemMgr::JmpHook(CameraEvent_addr, (uintptr_t)Asm_CameraEvent_V2);

#ifdef TESTING
			printf("HOOK V2 activated\n");
#endif

			return true;
		}

#ifdef TESTING
		printf("HOOK V2 don't work\n");
#endif

		return false;
	}


	bool Init()
	{
		g_pMod = Mod::Get();

#ifdef TESTING
		std::cout << "Initializing hooks...\n";
	#endif 

		if (Hook_V1())
		{
			return true;
		}

		if (Hook_V2())
		{
			return true;
		}

		Mod::Get()->Log(SCS_LOG_TYPE_error, "Data structure is incorrect!");
#ifdef TESTING
		std::cout << "Hook for CameraEvent not found!\n";
#endif
		return false;
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
