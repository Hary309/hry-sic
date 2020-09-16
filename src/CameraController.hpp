#pragma once

#include "Game/InteriorCamera.hpp"

#include "Camera.hpp"

struct ConfigData;

class CameraController
{
private:
    Camera _camera;

public:
    CameraController();

    void update(float deltaTime);

    void applyConfig(const ConfigData& configData);

private:
    void onGameCameraUpdate(const prism::InteriorCamera&& interiorCamera);
};
