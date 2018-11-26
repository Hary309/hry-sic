/** @file Camera.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include "Game/prism.h"

class Camera
{
	enum MoveTo
	{
		BIGGER,
		SMALLER
	};		

private:
	prism::CameraV2Pos	*m_pGameCamera = nullptr;

	MoveTo			m_moveType;

	float			m_rxCurr = 0.f;
	float			m_rxEnd = 0.f;

	float			m_delta;
	int				m_dir;

	float			m_acceleration;
	float			m_speed = 0.01f;

	int				m_movingStage;

	bool			m_anim = false;
	bool			m_stopInNextPulse = false;

	const float MAX_LINEARLY_SPEED = 0.12f;
	const float MAX_SMOOTH_SPEED = 0.01f;

public:
	Camera();
	~Camera();

	void MoveTo(float rx);
	void UpdateRX(float rx) { m_rxCurr = rx; }

	void UpdateGameCamera(prism::CameraV2Pos *gameCamera) { m_pGameCamera = gameCamera; }

	prism::CameraV2Pos *GetGameCamera() { return m_pGameCamera; }

	void Pulse();

	bool IsAnimation() { return m_anim; }
};
