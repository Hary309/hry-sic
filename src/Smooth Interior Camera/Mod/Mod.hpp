/** @file Mod.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <memory>
#include <Windows.h>
#include <sstream>

#include <scssdk_telemetry.h>

#include "Config.hpp"
#include "Camera.hpp"

class Mod
{
private:
	std::unique_ptr<Camera>	m_pCam;
	Config					m_config;
	bool					m_active = true;

	bool					m_configurating = false;

	bool					m_playing = false;

	uint64_t				m_tDelay;

	scs_log_t				m_logFunc;

	static Mod				*s_pInst;

public:
	Mod();
	~Mod();

	int Init(scs_telemetry_init_params_v100_t* scsTelemetry);

	void Pulse();

	template<typename... Us>
	void Log(scs_log_type_t logType, Us... args)
	{
		std::stringstream sstream;

		sstream << "[SIC] ";

		((sstream << args), ...);

#ifdef TESTING
		std::cout << sstream.str() << "\n";
#endif

		if (m_logFunc)
			m_logFunc(logType, sstream.str().c_str());
	}


	bool IsActive()			{ return m_active; }
	bool IsConfiguring()	{ return m_configurating; }
	bool IsPlaying()		{ return m_playing; }

	void DisableConfigurating();

	Camera *GetCamera()		{ return m_pCam.get(); }
	static Mod *Get()		{ return s_pInst; }

	static void __stdcall TelemetryFrameEnd(const scs_event_t, const void *const, const scs_context_t);
	static void __stdcall TelemetryPause(const scs_event_t event, const void *const, const scs_context_t);
};

