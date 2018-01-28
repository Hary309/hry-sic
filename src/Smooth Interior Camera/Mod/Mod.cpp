/*
*********************************************************************
* File			: Mod.cpp
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#include "Mod.h"

#include <cstdio>
#include <Windows.h>

#include "Memory\MemMgr.h"
#include "Game\Hooks.h"
#include "Mod\Camera.h"
#include "Mod\Config.h"
#include "Common.h"

Mod *Mod::s_pInst;

Mod::Mod()
{
	s_pInst = this;
}

Mod::~Mod()
{
}

int Mod::Init(scs_telemetry_init_params_v100_t* scsTelemetry)
{
#ifdef TESTING
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stdin);
#endif

	m_logFunc = scsTelemetry->common.log;
	
#ifdef ATS
	std::string forumLink = "https://forum.scssoft.com/viewtopic.php?t=248870";
#elif ETS2
	std::string forumLink = "https://forum.scssoft.com/viewtopic.php?t=223989";
#endif

#ifdef TESTING
	printf("Base address = %I64u\n", (uintptr_t)(GetModuleHandle(0) - 0x000140000000));
#endif

	if (!Hooks::Init())
	{
		Mod::Log(SCS_LOG_TYPE_error, "This version isn't supported! Check (%s) for updates", forumLink.c_str());
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
		if (GetForegroundWindow() != GetActiveWindow())
			return;

		if (!m_active)
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
		if (GetForegroundWindow() != GetActiveWindow())
			return;

		if (!m_active)
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

	char buffer2[256];

	sprintf(buffer2, "[SIC] %s", buffer);

#ifdef TESTING
	puts(buffer2);
#endif

	if (m_logFunc)
		m_logFunc(logType, buffer2);
}

void Mod::DisableConfigurating()
{
	Mod::Log(SCS_LOG_TYPE_message, "Configurating deactivated");
	m_configurating = false;
}
