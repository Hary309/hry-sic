/** @file prism.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include "Version.hpp"

namespace prism
{
	class InteriorCamera
	{
	public:
		unsigned m_keyboardEv;	// +0
		float m_rxEnd;			// +4
		float m_ryEnd;			// +8
		// +12
	};	

	class InteriorCameraPos
	{
	public:
		float m_rx;		// +0
		float m_ry;		// +4
		// +8
	};
}
