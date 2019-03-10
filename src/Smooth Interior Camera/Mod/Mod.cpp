/** @file Mod.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "Mod.hpp"

#include <cstdio>
#include <Windows.h>
#include <iostream>

#include "Memory/MemMgr.hpp"
#include "Game/Hooks.hpp"
#include "Mod/Camera.hpp"
#include "Mod/Config.hpp"
#include "Common.hpp"

Mod *Mod::s_pInst;

Mod::Mod()
{
	s_pInst = this;
}

Mod::~Mod()
{
	Hooks::Unhook();
}

int Mod::Init(scs_telemetry_init_params_v100_t *scsTelemetry)
{
#ifdef TESTING
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stdin);
#endif

	m_logFunc = scsTelemetry->common.log;

	Mod::Log(SCS_LOG_TYPE_message, "Initializing mod...");
	
	const char* forumLinkETS2 = "https://forum.scssoft.com/viewtopic.php?t=223989";
	const char* forumLinkATS = "https://forum.scssoft.com/viewtopic.php?t=248870";

#ifdef TESTING
	std::cout << "Base address = " << std::hex << std::uppercase << reinterpret_cast<uintptr_t>(GetModuleHandle(0) - 0x000140000000) << "\n";
#endif

	if (!Hooks::Init())
	{
		Mod::Log(SCS_LOG_TYPE_error, "This version of game isn't supported! Check ", forumLinkETS2, " or ", forumLinkATS, " for updates");
		return SCS_RESULT_unsupported;
	}

	int init = 0;

	init += scsTelemetry->register_for_event(SCS_TELEMETRY_EVENT_frame_end, TelemetryFrameEnd, nullptr) == SCS_RESULT_ok ? 1 : 0;
	init += scsTelemetry->register_for_event(SCS_TELEMETRY_EVENT_paused, TelemetryPause, nullptr) == SCS_RESULT_ok ? 1 : 0;
	init += scsTelemetry->register_for_event(SCS_TELEMETRY_EVENT_started, TelemetryPause, nullptr) == SCS_RESULT_ok ? 1 : 0;

	if (init != 3) 
	{
		Mod::Log(SCS_LOG_TYPE_error, "Unable to register event callbacks");
		return SCS_RESULT_generic_error;
	}

	m_config.Load();

	m_active = m_config.m_active;

	m_pCam = std::make_unique<Camera>();

	Mod::Log(SCS_LOG_TYPE_message, "Mod initialized!");

	return SCS_RESULT_ok;
}

void Mod::TelemetryFrameEnd(const scs_event_t, const void *const, const scs_context_t)
{
	auto mod = Mod::Get();

	if (mod->IsPlaying())
		mod->Pulse();
}

void Mod::TelemetryPause(const scs_event_t event, const void *const, const scs_context_t)
{
	Mod::Get()->m_playing = (event == SCS_TELEMETRY_EVENT_started);
}

void Mod::Pulse()
{
	if (IsActive())
		m_pCam->Pulse();

	if (GetAsyncKeyState(VK_INSERT))
	{
		if (m_config.m_disableShortcuts)
			return;

		if (GetForegroundWindow() != GetActiveWindow())
			return;

		if (m_tDelay + 1000 < GetTickCount())
		{
			m_active = !m_active;

			Mod::Log(SCS_LOG_TYPE_message, "Mod ", m_active ? "activated" : "deactivated");

			m_config.m_active = m_active;

			Config::Get()->Save();

			m_tDelay = GetTickCount();
		}
	}

	if (GetAsyncKeyState(VK_DELETE))
	{
		if (m_config.m_disableShortcuts)
			return;

		if (GetForegroundWindow() != GetActiveWindow())
			return;

		if (m_tDelay + 1000 < GetTickCount())
		{
			m_configurating = !m_configurating;

			Mod::Log(SCS_LOG_TYPE_message, "Configuration ", m_configurating ? "activated" : "deactivated");

			if (m_configurating == true)
				Mod::Log(SCS_LOG_TYPE_message, "Now set camera (with mouse) and push the button which you want to look here");

			m_tDelay = GetTickCount();
		}
	}

	if (GetAsyncKeyState(VK_HOME))
	{
		if (m_config.m_disableShortcuts)
			return;

		if (GetForegroundWindow() != GetActiveWindow())
			return;

		if (m_tDelay + 1000 < GetTickCount())
		{
			Mod::Log(SCS_LOG_TYPE_message, "Reloading settings...");

			m_config.Load();

			m_active = m_config.m_active;

			m_tDelay = GetTickCount();
		}
	}
}

void Mod::DisableConfigurating()
{
	Mod::Log(SCS_LOG_TYPE_message, "Configurating deactivated");
	m_configurating = false;
}
