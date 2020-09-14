#pragma once

#include "Camera.hpp"

struct ConfigData
{
    float speed{};
    Camera::RotationStyle rotationStyle{};
    float cameraPosition[6]{};
};
