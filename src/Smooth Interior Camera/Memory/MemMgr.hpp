/** @file MemMgr.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <cstdint>

class MemMgr
{
public:
	static void UnprotectMemory(uintptr_t addr, size_t size);

	static void JmpHook(uintptr_t addr, uintptr_t addrTo);
};

