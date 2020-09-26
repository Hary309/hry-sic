#pragma once

#include <array>

#include "Game/InteriorCamera.hpp"

#include "Camera.hpp"

struct ConfigData;

class CameraController
{
private:
    Camera _camera;

    std::array<float, 6> _cameraRotation;

public:
    CameraController();

    void update(float deltaTime);

    void applyConfig(const ConfigData& configData);

    Camera& getCamera() { return _camera; }

private:
    void onGameCameraUpdate(const prism::InteriorCamera&& interiorCamera);
};
