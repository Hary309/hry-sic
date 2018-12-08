/** @file Camera.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include "Game/prism.h"

class Camera
{
private:
	prism::GameCameraPos *m_pGameCamera = nullptr;

	float	m_rxCurr = 0.f;
	float	m_rxStart = 0.f;
	float	m_rxEnd = 0.f;

	float	m_delta = 0.f;

	float	m_progress = 0.f;

	float	m_speed = 0.01f;

	bool	m_anim = false;

	const float MAX_LINEARLY_SPEED = 0.12f;
	const float MAX_EASEINOUT_SPEED = 0.1f;

public:
	Camera();
	~Camera();

	void MoveTo(float rx);
	void UpdateRX(float rx) { m_rxCurr = rx; }

	void UpdateGameCamera(prism::GameCameraPos *gameCamera) { m_pGameCamera = gameCamera; }

	prism::GameCameraPos *GetGameCamera() { return m_pGameCamera; }

	void Pulse();

	bool IsAnimation() { return m_anim; }
};
