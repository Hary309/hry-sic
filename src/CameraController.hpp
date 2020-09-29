#pragma once

#include <array>

#include "Hry/KeyBinding/BindableKeys.hpp"

#include "Game/InteriorCamera.hpp"

#include "Camera.hpp"

struct ConfigData;

class CameraController
{
private:
    Camera _camera;

    std::array<float, 6> _cameraRotation;

    bool _disableInGameEvent = false;
    bool _autoCenter = false;
    float _verticalAngle = 0.f;

    Camera::Position _selectedPosition = Camera::Position::InteriorLookForward;

public:
    CameraController();

    void update(float deltaTime);

    void applyConfig(const ConfigData& configData);

    Camera& getCamera() { return _camera; }

    void onKeyBindPress(Camera::Position position);
    void onKeyBindRelease(Camera::Position position);

private:
    void onGameCameraUpdate(const prism::InteriorCamera&& interiorCamera);
};