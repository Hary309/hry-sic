/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#pragma once

#include "Common.hpp"

namespace prism
{
    struct InteriorCameraEvent
    {
        bool event;    // +0 change camera position key is pressed
        Rotation dest; // +4 Destination rotation
    };

    struct InteriorCamera
    {
        prism::InteriorCameraEvent* event;
        Rotation* rotation;
    };
} // namespace prism
