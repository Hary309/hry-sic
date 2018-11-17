/*
*********************************************************************
* File			: Mod.h
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#pragma once

#include <memory>
#include <Windows.h>

#include <scssdk_telemetry.h>

#include "Config.h"
#include "Camera.h"

class Mod
{
private:
	std::unique_ptr<Camera>				m_pCam;
	Config								m_config;
	bool								m_active = true;

	bool								m_configurating = false;

	bool								m_playing = false;

	unsigned							m_tDelay;

	scs_log_t							m_logFunc;

	static Mod							*s_pInst;

public:
	Mod();
	~Mod();

	int Init(scs_telemetry_init_params_v100_t* scsTelemetry);

	void Pulse();

	void Log(scs_log_type_t logType, const char *str, ...);

	bool IsActive()			{ return m_active; }
	bool IsConfiguring()	{ return m_configurating; }
	bool IsPlaying()		{ return m_playing; }

	void DisableConfigurating();

	Camera *GetCamera()		{ return m_pCam.get(); }
	static Mod *Get()		{ return s_pInst; }

	static void TelemetryFrameEnd(const scs_event_t, const void *const, const scs_context_t);
	static void TelemetryPause(const scs_event_t event, const void *const, const scs_context_t);
};

