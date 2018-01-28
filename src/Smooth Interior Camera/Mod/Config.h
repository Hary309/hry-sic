/*
*********************************************************************
* File			: Config.h
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#pragma once

#include <string>
#include <vector>

class Config
{
private:
	static Config *s_pInst;

	float m_defaultValues[6];

public:
	enum RotationStyle
	{
		LINEAR = 0,
		SMOOTH
	};

	// global settings with default values
	bool			m_active = true;
	int				m_speed = 70;
	bool			m_disableShortcuts = false;
	RotationStyle	m_rotationStyle = SMOOTH;

	float	m_interiorCamPos[6];


	enum CameraPos
	{
		INTERIOR_LOOK_FORWARD = 0,
		INTERIOR_LOOK_UP_RIGHT,
		INTERIOR_LOOK_UP_LEFT,
		INTERIOR_LOOK_RIGHT,
		INTERIOR_LOOK_LEFT,
		INTERIOR_LOOK_UP_MIDDLE
	};

	const std::string m_settingsPath = "plugins\\sic_settings.txt";

public:
	Config();
	~Config();

	void Load();
	void Save();

	void CreateDefaultFile();

	// @pos enum: CameraPos
	float GetDefaultValue(unsigned pos) { return m_defaultValues[pos]; }
	// @pos enum: CameraPos
	float GetValue(unsigned pos) { return m_interiorCamPos[pos]; }

	static Config *Get() { return s_pInst; }
};

