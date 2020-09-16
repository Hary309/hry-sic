#pragma once

namespace prism
{
    struct InteriorCameraEvent
    {
        unsigned event; // +0 change camera position key is pressed
        float rxEnd;    // +4 Destination rotation x
        float rzEnd;    // +8 Destination rotation y
                        // +12
    };

    struct InteriorCameraPos
    {
        float rx; // +0 current rotation x
        float rz; // +4 current rotation z
                  // +8
    };

    struct InteriorCamera
    {
        prism::InteriorCameraEvent* event;
        prism::InteriorCameraPos* pos;
    };
} // namespace prism
