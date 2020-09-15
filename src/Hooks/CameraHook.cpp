#include "CameraHook.hpp"

#include <memory>

#include <Hry/Memory/Detour.hpp>
#include <Hry/Memory/Hooking.Patterns.hpp>

#include "Game/InteriorCamera.hpp"

#include "SIC.hpp"

static std::uint16_t gameCamOffset = 0;
static std::uint16_t gameCamPosOffset = 0;
static std::unique_ptr<hry::Detour> detour;

extern "C"
{
    uintptr_t CameraEvent_CallAddress = 0;
    uintptr_t CameraEvent_RetnAddress = 0;

    void Asm_CameraEvent_V2();

    asm(R"(
        .extern CameraEvent_CallAddress: qword
        .extern CameraEvent_RetnAddress: qword
    
    Asm_CameraEvent_V2:
        push    %rax
        push    %rbx
        push    %rcx
        push    %rdx
        push    %rsi
        push    %rdi
        push    %rbp
        push    %r8
        push    %r9
        push    %r10
        push    %r11
        push    %r12
        push    %r13
        push    %r14
        push    %r15

        push %rcx
	    mov %rdi, %rcx
        call *CameraEvent_CallAddress(%rip)
        pop %rcx

        pop     %r15
        pop     %r14
        pop     %r13
        pop     %r12
        pop     %r11
        pop     %r10
        pop     %r9
        pop     %r8
        pop     %rbp
        pop     %rdi
        pop     %rsi
        pop     %rdx
        pop     %rcx
        pop     %rbx
        pop     %rax

        jmp *CameraEvent_RetnAddress(%rip)
    )");
}

void __stdcall CameraEvent(uintptr_t gameCamera, float unk)
{
    auto pGameCam = reinterpret_cast<prism::InteriorCamera*>(gameCamera + gameCamOffset);
    auto pGameCamPos = reinterpret_cast<prism::InteriorCameraPos*>(gameCamera + gameCamPosOffset);

    SIC::Logger->info("{} {}, {} {}", pGameCamPos->rx, pGameCamPos->ry, pGameCam->rxEnd, pGameCam->ryEnd);

    detour->getOriginal<decltype(CameraEvent)>()(gameCamera, unk);
}

bool CameraHook::Install()
{
    hry::pattern CameraUpdate_pattern(std::string_view("48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 48 8D ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 48 8B F9  0F 29 ? ?  44 0F ? ? ?  44 0F ? ? ?  44 0F ? ? ?  44 0F ? ? ?"));
    hry::pattern CameraUpdate_dataFields(std::string_view("F3 0F 10 ? ? ? 00 00  F3 0F 10 ? ? ? 00 00  83 F8 01  75 ?  F3 0F 11 ? ? ? 00 00  F3 0F 11 ? ? ? 00 00  89 9F ? ? 00 00  E9 ? ? 00 00"));

    SIC::Logger->info("Searching for pattern3...");

    if (CameraUpdate_pattern.size() > 0 && CameraUpdate_dataFields.size() > 0)
    {
        uintptr_t CameraUpdate_addr = reinterpret_cast<uintptr_t>(CameraUpdate_pattern.count(1).get(0).get<uintptr_t>(0));
        uintptr_t CameraUpdate_dataOffset = reinterpret_cast<uintptr_t>(CameraUpdate_dataFields.count(1).get(0).get<uintptr_t>(0));

        gameCamOffset = *reinterpret_cast<std::uint16_t*>(CameraUpdate_dataOffset + 25) - 4;
        gameCamPosOffset = *reinterpret_cast<std::uint16_t*>(CameraUpdate_dataOffset + 25);

        detour = std::unique_ptr<hry::Detour>(new hry::Detour((void*)CameraUpdate_addr, (void*)CameraEvent));

        if (detour->hook() != hry::Detour::Status::Ok)
        {
            SIC::Logger->error("Cannot hook");
            return false;
        }

        if (detour->enable() != hry::Detour::Status::Ok)
        {
            SIC::Logger->error("Cannot enable hook");
            return false;
        }

        SIC::Logger->info("Hook successfully installed");

        return true;
    }

    return false;
}

void CameraHook::Uninstall()
{
    detour.reset();
}
