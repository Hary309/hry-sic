#pragma once

#include "Camera.hpp"

struct ConfigData
{
    float speed{};
    Camera::RotationStyle rotationStyle{};
    bool centerVertically{};
    float cameraPosition[6]{};
};
