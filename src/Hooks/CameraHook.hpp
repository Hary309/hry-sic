#pragma once

#include <Hry/Utils/Delegate.hpp>

#include "Game/InteriorCamera.hpp"

struct CameraHook
{
    inline static hry::Delegate<void(const prism::InteriorCamera&&)> OnCameraUpdate;

    static bool Install();
    static void Uninstall();
};
