/*
*********************************************************************
* File			: prism.h
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#pragma once

namespace prism
{
	class Camera
	{
	public:
		char pad1[684];			// +0
		unsigned m_keyboardEv;	// +684
		float m_rx_predef;		// +688
		float m_ry_predef;		// +692
		char pad3[144];			// +696
		float m_rx;				// +840 main camera
		float m_ry;				// +844
	};
}