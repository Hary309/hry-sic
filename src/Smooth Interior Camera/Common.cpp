/*
*********************************************************************
* File			: Common.cpp
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#include "Common.h"

#include <cmath>

bool floatEquals(float a, float b, float epsilon)
{
	return fabs(a - b) < epsilon;
}
