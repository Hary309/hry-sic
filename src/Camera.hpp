#pragma once

#include "easing.hpp"

#include "Game/InteriorCamera.hpp"

class CameraController;

class Camera
{
    friend CameraController;



public:
    enum class RotationStyle
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

private:
    Easing::Function_t<float> _easingFunction = Easing::QuadraticEaseInOut;

    Rotation* _cameraRotation{};

    RotationStyle _rotationStyle = RotationStyle::EaseInOut;
    bool _centerVertically = true;

    float _speed{};
    float _speedFactor = 0.75f;

    bool _isAnimationPlaying = false;
    float _progress{};
    Rotation _animationStart{};
    Rotation _animationEnd{};
    Rotation _delta{};

private:
    const float MaxSpeed = 10.f;

public:
    Camera();

    void update(float deltaTime);

    void rotateTo(Rotation rotation);

    void setRotation(Rotation rotation);

};
