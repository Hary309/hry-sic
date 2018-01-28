/*
*********************************************************************
* File			: MemMgr.h
* Project		: Smooth Interior Camera
* Developers	: Piotr Krupa (piotrkrupa06@gmail.com)
* License		: MIT License
*********************************************************************
*/

#pragma once

#include <cstdint>

class MemMgr
{
public:
	static void UnprotectMemory(uintptr_t addr, size_t size);

	// 16 bytes
	static void LongJmpHook(uintptr_t addr, uintptr_t addrTo);
};

