/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#include "DefaultRotations.hpp"

#include <cmath>

#include "SIC.hpp"

float DefaultRotations::GetRotation(Camera::Position position)
{
    switch (position)
    {
        case Camera::Position::InteriorLookForward: return Rotations[0];
        case Camera::Position::InteriorLookUpRight: return Rotations[1];
        case Camera::Position::InteriorLookUpLeft: return Rotations[2];
        case Camera::Position::InteriorLookRight: return Rotations[3];
        case Camera::Position::InteriorLookLeft: return Rotations[4];
        case Camera::Position::InteriorLookUpMiddle: return Rotations[5];
    };
}

Camera::Position DefaultRotations::GetPosition(float rotation)
{
    auto it = std::find_if(Rotations.begin(), Rotations.end(), [&rotation](float inner) {
        return std::abs(rotation - inner) < 0.001f;
    });

    if (it != Rotations.end())
    {
        return static_cast<Camera::Position>(std::distance(Rotations.begin(), it));
    }

    return Camera::Position::InteriorLookForward;
}