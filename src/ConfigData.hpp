/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#pragma once

#include <array>

#include "Camera.hpp"

struct ConfigData
{
    float speed{};
    Camera::RotationStyle rotationStyle{};
    bool centerVertically{};
    std::array<float, 6> cameraRotation;

    bool experimentalFeatures;
    float verticalAngle;
    bool autoCenter;
};
