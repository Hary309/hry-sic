#pragma once

namespace prism
{
    struct InteriorCamera
    {
        unsigned keyboardEv; // +0
        float rxEnd;         // +4
        float ryEnd;         // +8
                             // +12
    };

    struct InteriorCameraPos
    {
        float rx; // +0
        float ry; // +4
                  // +8
    };
} // namespace prism
