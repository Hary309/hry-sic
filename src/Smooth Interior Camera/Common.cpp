/** @file Common.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "Common.h"

#include <cmath>

bool floatEquals(float a, float b, float epsilon)
{
	return fabs(a - b) < epsilon;
}
