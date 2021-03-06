/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#include "Camera.hpp"

#include "SIC.hpp"

Camera::Camera()
{
}

void Camera::update(float deltaTime)
{
    if (_cameraRotation == nullptr)
    {
        return;
    }

    if (_isAnimationPlaying)
    {
        _progress += _speed * deltaTime;

        if (_progress >= 1.f)
        {
            _progress = 1.f;
            _isAnimationPlaying = false;
        }

        auto result = _animationStart + _delta * _easingFunction(_progress);

        _cameraRotation->x = result.x;

        if (_centerVertically)
        {
            _cameraRotation->y = result.y;
        }
    }
}

void Camera::rotateTo(Rotation rotation)
{
    if (_cameraRotation == nullptr)
    {
        return;
    }

    if (_cameraRotation->x == rotation.x)
    {
        _cameraRotation->y = rotation.y;
        return;
    }

    _animationStart = *_cameraRotation;
    _animationEnd = rotation;

    _delta = _animationEnd - _animationStart;
    auto delta = std::abs(_animationStart.x - _animationEnd.x);

    _progress = 0.f;

    switch (_rotationStyle)
    {
        case RotationStyle::EaseInOut: _easingFunction = hry::Easing::QuadraticEaseInOut; break;
        case RotationStyle::EaseOut: _easingFunction = hry::Easing::QuadraticEaseOut; break;
        case RotationStyle::Linear: _easingFunction = hry::Easing::LinearInterpolation; break;
    }

    _speed = (MaxSpeed * _speedFactor) / ((delta / 2.f) + 1.f);

    SIC::Logger->info("Rotating to {} with speed {}", _animationEnd, _speed);

    _isAnimationPlaying = true;
}

void Camera::setRotation(Rotation rotation)
{
    if (_cameraRotation)
    {
        *_cameraRotation = rotation;
    }
}

void Camera::setRX(float rotation)
{
    if (_cameraRotation)
    {
        _cameraRotation->x = rotation;
    }
}

void Camera::setRY(float rotation)
{
    if (_cameraRotation)
    {
        _cameraRotation->y = rotation;
    }
}
