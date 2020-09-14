#pragma once

class Camera
{
public:
    enum RotationStyle
    {
        Linear = 0,
        EaseInOut,
        EaseOut
    };

    enum class Position
    {
        InteriorLookForward = 0,
        InteriorLookUpRight,
        InteriorLookUpLeft,
        InteriorLookRight,
        InteriorLookLeft,
        InteriorLookUpMiddle
    };
};
