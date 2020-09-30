/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#pragma once

#include <Hry/Utils/Delegate.hpp>

#include "Game/InteriorCamera.hpp"

struct CameraHook
{
    inline static hry::Delegate<void(const prism::InteriorCamera&&)> OnCameraUpdate;

    static bool Install();
    static void Uninstall();
};
