/*
*********************************************************************
* File			: Camera.cpp
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#include "Camera.h"

#include <Windows.h>
#include <iostream>

#include "Common.h"
#include "Config.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::MoveTo(float rx)
{
	if (rx == m_rxCurr)
		return;

	m_rxEnd = rx;

	m_delta = abs(m_rxCurr - m_rxEnd);

	if (m_rxCurr > m_rxEnd)
		m_dir = -1;
	else if (m_rxCurr < m_rxEnd)
		m_dir = 1;

	if (Config::Get()->m_rotationStyle == Config::LINEAR)
	{
		m_speed = (Config::Get()->m_speed * MAX_LINEARLY_SPEED) / 100;
	}
	else if (Config::Get()->m_rotationStyle == Config::SMOOTH)
	{
		m_acceleration = (Config::Get()->m_speed * MAX_SMOOTH_SPEED) / 100;
		m_speed = 0.f;
		m_movingStage = 1;
	}

	m_stopInNextPulse = false;

#ifdef TESTING
	std::cout << "Moving to " << m_rxEnd << "\n";
#endif

	m_anim = true;
}

void Camera::Pulse()
{
	if (m_pGameCamera == nullptr)
		return;

	if (m_anim)
	{
		m_pGameCamera->m_rx = m_rxCurr;

		if (m_stopInNextPulse)
		{
			m_anim = false;
			m_stopInNextPulse = false;
			return;
		}

		if (Config::Get()->m_rotationStyle == Config::SMOOTH)
		{
			if (abs(m_rxCurr - m_rxEnd) >= m_delta / 2 && m_movingStage == 1)
			{
				m_speed += m_acceleration;
			}
			else
			{
				m_speed -= m_acceleration;

				if (m_speed <= 0.f)
					m_speed = m_acceleration;

				m_movingStage = 2;
			}
		}

		if (m_rxCurr * m_dir + m_speed < m_rxEnd * m_dir)
		{
			m_rxCurr += m_speed * m_dir;
		}
		else
		{
			m_rxCurr = m_rxEnd;
			m_stopInNextPulse = true;
		}
	}
	else
	{
		m_rxCurr = m_pGameCamera->m_rx;
	}
}
