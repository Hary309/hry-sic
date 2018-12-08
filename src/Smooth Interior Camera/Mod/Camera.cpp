/** @file Camera.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "Camera.hpp"

#include <Windows.h>
#include <iostream>

#include "Common.hpp"
#include "Config.hpp"

#include "AHEasing/easing.h"

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

	m_rxStart = m_rxCurr;
	m_rxEnd = rx;

	m_delta = abs(m_rxStart - m_rxEnd);

	m_progress = 0.f;

	switch (Config::Get()->m_rotationStyle)
	{
		case Config::EaseInOut:
		case Config::EaseOut:
		{
			m_speed = ((MAX_EASEINOUT_SPEED * Config::Get()->m_speed) / 100);
		} break;
		case Config::Linear:
		{
			m_speed = ((MAX_LINEARLY_SPEED * Config::Get()->m_speed) / 100);
		} break;
	}

	m_speed /= (((m_delta) / 2.f) + 1.f);

#ifdef TESTING
	std::cout << "Moving to " << m_rxEnd << " with speed " << m_speed << "\n";
#endif

	m_anim = true;
}

void Camera::Pulse()
{
	if (m_pGameCamera == nullptr)
		return;

	if (m_anim)
	{
		m_progress += m_speed;

		if (m_progress >= 1.f)
		{
			m_progress = 1.f;
			m_anim = false;
		}

		m_pGameCamera->m_rx = (m_rxEnd - m_rxStart);

		switch (Config::Get()->m_rotationStyle)
		{
			case Config::EaseInOut:
			{
				m_pGameCamera->m_rx *= QuadraticEaseInOut(m_progress);
			} break;
			case Config::EaseOut:
			{
				m_pGameCamera->m_rx *= QuadraticEaseOut(m_progress);
			} break;
			case Config::Linear:
			{
				m_pGameCamera->m_rx *= m_progress;
			} break;
		}

		m_pGameCamera->m_rx += m_rxStart;
	}
	else
	{
		m_rxCurr = m_pGameCamera->m_rx;
	}
}
