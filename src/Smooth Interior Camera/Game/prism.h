/** @file prism.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include "Version.h"

namespace prism
{
	template <size_t Offset1, size_t Offset2>
	class CameraBase
	{
	public:
		char pad1[Offset1];			// +0
		unsigned m_keyboardEv;		// +Offset1
		float m_rx_predef;			// +Offset1 + 4
		float m_ry_predef;			// +Offset1 + 8
		char pad2[Offset2];			// +Offset1 + 12
		float m_rx;					// +Offset2
		float m_ry;					// +Offset2 + 4
	};


#if defined(HOOK_V1)
	using Camera = CameraBase<684, 144>;
#elif defined(HOOK_V2)
	using Camera = CameraBase<692, 144>;
#endif
}
