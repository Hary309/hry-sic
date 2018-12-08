/** @file MemMgr.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "MemMgr.h"

#include <Windows.h>

#include "Version.h"

#ifdef X64
/*
	push rax
	mov rax addr   ; @addr - address to original
	xchg qword ptr ss:[rsp], rax
	ret
*/
unsigned char g_jmpHook[] = { 0x50, 0x48, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x87, 0x04, 0x24, 0xC3 };
#endif 

void MemMgr::UnprotectMemory(uintptr_t addr, size_t size)
{
	DWORD temp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &temp);
}

#if defined(X64)
void MemMgr::JmpHook(uintptr_t addr, uintptr_t addrTo)
{
	UnprotectMemory(addr, sizeof(g_jmpHook));

	// long jump
	memcpy((unsigned char*)addr, g_jmpHook, sizeof(g_jmpHook));
	*(uintptr_t*)&((unsigned char*)addr)[3] = addrTo;
}
#elif defined(X86)
void MemMgr::JmpHook(uintptr_t addr, uintptr_t addrTo)
{
	UnprotectMemory(addr, 5);

	*(unsigned char*)(addr) = 0xE9;
	*(unsigned*)(addr + 1) = addrTo - (addr + 5);

}
#endif
