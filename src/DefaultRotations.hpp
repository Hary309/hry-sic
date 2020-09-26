#pragma once

#include <array>

#include "Camera.hpp"

class DefaultRotations
{
private:
    static constexpr std::array<float, 6> Rotations = { 0.f,        -0.698132f, 0.349066f,
                                                        -1.221730f, 1.221730f,  -0.349066f };

public:
    static float GetRotation(Camera::Position position);
    static Camera::Position GetPosition(float rotation);
};
