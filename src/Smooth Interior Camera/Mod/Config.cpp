/*
*********************************************************************
* File			: Config.cpp
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#include "Config.h"

#include <cstdio>
#include <string>
#include <fstream>

#include <json.hpp>

#include "resource.h"
#include "Common.h"
#include "Mod.h"

Config *Config::s_pInst;

Config::Config()
{
	m_defaultValues[INTERIOR_LOOK_FORWARD]		= 0.f;
	m_defaultValues[INTERIOR_LOOK_UP_RIGHT]		= -0.698132f;
	m_defaultValues[INTERIOR_LOOK_UP_LEFT]		= 0.349066f;
	m_defaultValues[INTERIOR_LOOK_RIGHT]		= -1.221730f;
	m_defaultValues[INTERIOR_LOOK_LEFT]			= 1.221730f;
	m_defaultValues[INTERIOR_LOOK_UP_MIDDLE]	= -0.349066f;

	for (unsigned i = 0; i < 6; ++i)
	{
		m_interiorCamPos[i] = m_defaultValues[i];
	}

	s_pInst = this;
}

Config::~Config()
{
}

void Config::Load()
{
	std::fstream fs(m_settingsPath, std::fstream::in);

	if (!fs.is_open())
	{
		CreateDefaultFile();
		return;
	}

	nlohmann::json json;

	fs >> json;
	fs.close();

	if (!json["interior_look_forward"].is_null())
		m_interiorCamPos[INTERIOR_LOOK_FORWARD] = json["interior_look_forward"];

	if (!json["interior_look_up_right"].is_null())
		m_interiorCamPos[INTERIOR_LOOK_UP_RIGHT] = json["interior_look_up_right"];

	if (!json["interior_look_up_left"].is_null())
		m_interiorCamPos[INTERIOR_LOOK_UP_LEFT] = json["interior_look_up_left"];

	if (!json["interior_look_right"].is_null())
		m_interiorCamPos[INTERIOR_LOOK_RIGHT] = json["interior_look_right"];

	if (!json["interior_look_left"].is_null())
		m_interiorCamPos[INTERIOR_LOOK_LEFT] = json["interior_look_left"];

	if (!json["interior_look_up_middle"].is_null())
		m_interiorCamPos[INTERIOR_LOOK_UP_MIDDLE] = json["interior_look_up_middle"];

	if (json["version"].is_null())
	{
		CreateDefaultFile();
		return;
	}

	int version = json["version"];

#ifdef TESTING
	printf("Version: %d\n", version);
#endif

	if (version < 1008)
	{
		CreateDefaultFile();
		return;
	}

	if (!json["active"].is_null())
		m_active = json["active"];
	else
		Save();

	if (!json["speed"].is_null())
		m_speed = json["speed"];
	else
		Save();

	if (!json["disable_shortcuts"].is_null())
		m_disableShortcuts = json["disable_shortcuts"];
	else
		Save();

	if (!json["rotation_style"].is_null())
		m_rotationStyle = json["rotation_style"];
	else
		Save();

#ifdef TESTING
	printf("active: %s\n", m_active ? "true" : "false");
	printf("speed: %d\n", m_speed);
	printf("disable_shortcuts: %s\n", m_disableShortcuts ? "true" : "false");
	printf("rotation_style: %d\n", m_rotationStyle);
	printf("interior_look_forward: %f\n", m_interiorCamPos[INTERIOR_LOOK_FORWARD]);
	printf("interior_look_up_right: %f\n", m_interiorCamPos[INTERIOR_LOOK_UP_RIGHT]);
	printf("interior_look_up_left: %f\n", m_interiorCamPos[INTERIOR_LOOK_UP_LEFT]);
	printf("interior_look_right: %f\n", m_interiorCamPos[INTERIOR_LOOK_RIGHT]);
	printf("interior_look_left: %f\n", m_interiorCamPos[INTERIOR_LOOK_LEFT]);
	printf("interior_look_up_middle: %f\n\n", m_interiorCamPos[INTERIOR_LOOK_UP_MIDDLE]);
#endif
}

void Config::Save()
{
	std::fstream fs(m_settingsPath, std::ios_base::out);

	nlohmann::json json;

	json["version"] = CURRENT_VERSION_SHORT;
	json["active"] = m_active;
	json["speed"] = m_speed;
	json["disable_shortcuts"] = m_disableShortcuts;
	json["rotation_style"] = m_rotationStyle;
	json["interior_look_forward"] = m_interiorCamPos[INTERIOR_LOOK_FORWARD];
	json["interior_look_up_right"] = m_interiorCamPos[INTERIOR_LOOK_UP_RIGHT];
	json["interior_look_up_left"] = m_interiorCamPos[INTERIOR_LOOK_UP_LEFT];
	json["interior_look_right"] = m_interiorCamPos[INTERIOR_LOOK_RIGHT];
	json["interior_look_left"] = m_interiorCamPos[INTERIOR_LOOK_LEFT];
	json["interior_look_up_middle"] = m_interiorCamPos[INTERIOR_LOOK_UP_MIDDLE];

	fs << json;

	fs.close();

	Mod::Get()->Log(SCS_LOG_TYPE_message, "Settings has been saved!");
}

void Config::CreateDefaultFile()
{
	remove(m_settingsPath.c_str());

	Mod::Get()->Log(SCS_LOG_TYPE_message, "Creating default settings file...");

	// default settings
	m_active = true;
	m_speed = 75;
	m_disableShortcuts = false;
	m_rotationStyle = SMOOTH;

	for (unsigned i = 0; i < 6; ++i)
	{
		m_interiorCamPos[i] = m_defaultValues[i];
	}

	Save();
}