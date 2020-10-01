/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#include "CameraController.hpp"

#include "Hooks/CameraHook.hpp"

#include "ConfigData.hpp"
#include "SIC.hpp"

CameraController::CameraController()
{
    CameraHook::OnCameraUpdate.connect<&CameraController::onGameCameraUpdate>(this);
}

void CameraController::update(float deltaTime)
{
    _camera.update(deltaTime);
}

void CameraController::onGameCameraUpdate(const prism::InteriorCamera&& interiorCamera)
{
    _camera._cameraRotation = interiorCamera.rotation;

    if (interiorCamera.event->event > 0)
    {
        interiorCamera.event->event = 0;

        if (!_disableInGameEvent)
        {
            const auto& dest = interiorCamera.event->dest;

            const auto position = DefaultRotations::GetPosition(dest.x);

            _camera.rotateTo({ _cameraRotation[static_cast<int>(position)], dest.y });
        }
    }
}

void CameraController::applyConfig(const ConfigData& configData)
{
    _camera._speedFactor = configData.speed;
    _camera._centerVertically = configData.centerVertically;
    _camera._rotationStyle = configData.rotationStyle;

    _cameraRotation = configData.cameraRotation;
    _disableInGameEvent = configData.experimentalFeatures;
    _autoCenter = configData.autoCenter;
    _verticalAngle = configData.verticalAngle;
}

void CameraController::onKeyBindPress(Camera::Position position)
{
    if (_disableInGameEvent)
    {
        _camera.rotateTo({ _cameraRotation[static_cast<int>(position)], _verticalAngle });
        _selectedPosition = position;
    }
}

void CameraController::onKeyBindRelease(Camera::Position position)
{
    if (_disableInGameEvent && _autoCenter && position == _selectedPosition &&
        position != Camera::Position::InteriorLookForward)
    {
        _camera.rotateTo({ _cameraRotation[0], _verticalAngle });
    }
}
