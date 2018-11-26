/** @file Mod.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "Mod.h"

#include <cstdio>
#include <Windows.h>
#include <iostream>

#include "Memory/MemMgr.h"
#include "Game/Hooks.h"
#include "Mod/Camera.h"
#include "Mod/Config.h"
#include "Common.h"

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
	
	const char* forumLinkETS2 = "https://forum.scssoft.com/viewtopic.php?t=223989";
	const char* forumLinkATS = "https://forum.scssoft.com/viewtopic.php?t=248870";

#ifdef TESTING
	std::cout << "Base address = " << std::hex << std::uppercase << reinterpret_cast<uintptr_t>(GetModuleHandle(0) - 0x000140000000) << "\n";
#endif

	if (!Hooks::Init())
	{
		Mod::Log(SCS_LOG_TYPE_error, "This version isn't supported! Check %s or $s for updates", forumLinkETS2, forumLinkATS);
		return SCS_RESULT_unsupported;
	}

	int init = 0;

	init += scsTelemetry->register_for_event(SCS_TELEMETRY_EVENT_frame_end, TelemetryFrameEnd, nullptr) == SCS_RESULT_ok ? 1 : 0;
	init += scsTelemetry->register_for_event(SCS_TELEMETRY_EVENT_paused, TelemetryPause, nullptr) == SCS_RESULT_ok ? 1 : 0;
	init += scsTelemetry->register_for_event(SCS_TELEMETRY_EVENT_started, TelemetryPause, nullptr) == SCS_RESULT_ok ? 1 : 0;

	if (init != 3) 
	{
		Log(SCS_LOG_TYPE_error, "Unable to register event callbacks");
		return SCS_RESULT_generic_error;
	}

	m_config.Load();

	m_active = m_config.m_active;

	m_pCam = std::make_unique<Camera>();

	Mod::Log(SCS_LOG_TYPE_message, "Mod intialized!");

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

			Mod::Log(SCS_LOG_TYPE_message, "Mod %s", m_active ? "activated" : "deactivated");

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

			Mod::Log(SCS_LOG_TYPE_message, "Configuration %s", m_configurating ? "activated" : "deactivated");

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

void Mod::Log(scs_log_type_t logType, const char *str, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, str);
	vsnprintf(buffer, 256, str, args);
	va_end(args);

	std::string strBuffer = "[SIC] " + std::string(buffer);

#ifdef TESTING
	std::cout << strBuffer << "\n";
#endif

	if (m_logFunc)
		m_logFunc(logType, strBuffer.c_str());
}

void Mod::DisableConfigurating()
{
	Mod::Log(SCS_LOG_TYPE_message, "Configurating deactivated");
	m_configurating = false;
}
