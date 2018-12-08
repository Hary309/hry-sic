/** @file Config.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

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
		Linear = 0,
		EaseInOut,
		EaseOut
	};

	// global settings with default values
	bool			m_active = true;
	int				m_speed = 75;
	bool			m_disableShortcuts = false;
	RotationStyle	m_rotationStyle = EaseInOut;

	float	m_interiorCamPos[6];


	enum GameCameraPos
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

