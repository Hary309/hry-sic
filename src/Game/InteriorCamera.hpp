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
