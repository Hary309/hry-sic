#pragma once

#include "Camera.hpp"

struct RotationConverter
{
    static constexpr float GetRotation(float normalized)
    {
        if (normalized > 0)
        {
            return normalized * Camera::MaxRight;
        }
        else if (normalized < 0)
        {
            return -normalized * Camera::MaxLeft;
        }

        return 0.f;
    }

    static constexpr float GetNormalized(float rotation)
    {
        if (rotation < 0)
        {
            return rotation / Camera::MaxRight;
        }
        else if (rotation > 0)
        {
            return -rotation / Camera::MaxLeft;
        }

        return 0.f;
    }
};
