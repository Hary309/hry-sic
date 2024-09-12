/**
 * This file is part of the hry-sic project
 * @ Author: Piotr Krupa <piotrkrupa06@gmail.com>
 * @ License: MIT License
 */

#include "SIC.hpp"

#include <string>

#include <Hry/Config/Fields/BoolField.hpp>
#include <Hry/Config/Fields/NumericField.hpp>
#include <Hry/Config/Fields/SelectionField.hpp>

#include "Hooks/CameraHook.hpp"

#include "Camera.hpp"
#include "ConfigData.hpp"

struct InternalConfigData
{
    float speed{};
    std::string rotationStyle;
    bool centerVertically;
    float lookForward;
    float lookUpRight;
    float lookUpLeft;
    float lookRight;
    float lookLeft;
    float lookUpMiddle;

    bool experimentalFeatures;
    float verticalAngle;
    bool autoCenter;
};

SIC::SIC() : _cameraController(_isGamePaused)
{
    fillPluginInfo();
}

SIC::Result SIC::init(const SIC::InitParams&& initParams)
{
    Logger = initParams.logger;

    if (!CameraHook::Install())
    {
        return SIC::Result::GameNotSupported;
    }

    return SIC::Result::Ok;
}

void SIC::initConfig(hry::Config* config)
{
    config->setBindingType<InternalConfigData>();
    config->onChangesApplied.connect<&SIC::onConfigChangesApplied>(this);

    config->add(hry::NumericFieldBuilder<float>()
                    .setID("animation_speed")
                    .setLabel("Animation speed")
                    .setDescription("Determines how fast camera rotate")
                    .useSlider(0.f, 1.f)
                    .bind(&InternalConfigData::speed)
                    .setDefaultValue(0.50f)
                    .build());

    config->add(hry::SelectionFieldBuilder()
                    .setID("rotation_style")
                    .setLabel("Rotation style")
                    .addOptions("Linear", "EaseInOut", "EaseOut")
                    .setDefaultValue("EaseInOut")
                    .bind(&InternalConfigData::rotationStyle)
                    .build());

    config->add(hry::BoolFieldBuilder()
                    .setID("center_vertically")
                    .setLabel("Center vertically")
                    .setDefaultValue(true)
                    .bind(&InternalConfigData::centerVertically)
                    .build());

    addRotationField(
        config, "look_forward", "Look Forward", Camera::Position::InteriorLookForward,
        &InternalConfigData::lookForward);
    addRotationField(
        config, "look_up_middle", "Look Up Middle", Camera::Position::InteriorLookUpMiddle,
        &InternalConfigData::lookUpMiddle);
    addRotationField(
        config, "look_up_left", "Look Up Left", Camera::Position::InteriorLookUpLeft,
        &InternalConfigData::lookUpLeft);
    addRotationField(
        config, "look_up_right", "Look Up Right", Camera::Position::InteriorLookUpRight,
        &InternalConfigData::lookUpRight);
    addRotationField(
        config, "look_left", "Look Left", Camera::Position::InteriorLookLeft,
        &InternalConfigData::lookLeft);
    addRotationField(
        config, "look_right", "Look Right", Camera::Position::InteriorLookRight,
        &InternalConfigData::lookRight);

    config->add(hry::BoolFieldBuilder()
                    .setID("experimental_features")
                    .setLabel("Experimental features")
                    .setDescription("This turns on custom keybinds and every field below work "
                                    "only when this field is enabled")
                    .setDefaultValue(false)
                    .bind(&InternalConfigData::experimentalFeatures)
                    .build());

    config->add(hry::NumericFieldBuilder<float>()
                    .setID("vertical_angle")
                    .setLabel("Vertical angle")
                    .setDescription("Only work when 'Experimental features' is enabled")
                    .bind(&InternalConfigData::verticalAngle)
                    .setDefaultValue(0.f)
                    .useDrag(0.001f, -1.f, 1.f)
                    .setPreviewCallback(hry::Dlg<&SIC::previewRotationVertical>(this))
                    .build());

    config->add(hry::BoolFieldBuilder()
                    .setID("auto_center")
                    .setLabel("Auto-Center")
                    .setDescription("Only work when 'Experimental features' is enabled")
                    .bind(&InternalConfigData::autoCenter)
                    .build());
}

void SIC::initKeyBinds(hry::KeyBinds* keyBinds)
{
    using Position = Camera::Position;

    addRotationKeybind<Position::InteriorLookForward>(
        keyBinds, "look_forward", "Look Forward", hry::Keyboard::Key::Numpad5);

    addRotationKeybind<Position::InteriorLookUpMiddle>(
        keyBinds, "look_up_middle", "Look Up Middle", hry::Keyboard::Key::Numpad8);

    addRotationKeybind<Position::InteriorLookUpLeft>(
        keyBinds, "look_up_left", "Look Up Left", hry::Keyboard::Key::Numpad7);

    addRotationKeybind<Position::InteriorLookUpRight>(
        keyBinds, "look_up_right", "Look Up Right", hry::Keyboard::Key::Numpad9);

    addRotationKeybind<Position::InteriorLookLeft>(
        keyBinds, "look_left", "Look Left", hry::Keyboard::Key::Numpad4);

    addRotationKeybind<Position::InteriorLookRight>(
        keyBinds, "look_right", "Look Right", hry::Keyboard::Key::Numpad6);
}

void SIC::initEvents(hry::EventDispatcher* dispatcher)
{
    dispatcher->game.onFrameStart.connect<&SIC::onFrameStart>(this);
}

const hry::PluginInfo& SIC::getPluginInfo() const
{
    return _pluginInfo;
}

void SIC::onConfigChangesApplied(const hry::ConfigCallbackData& callbackData)
{
    auto* data = callbackData.getData<InternalConfigData>();

    ConfigData configData;

    configData.speed = data->speed;
    configData.centerVertically = data->centerVertically;

    if (data->rotationStyle == "Linear")
        configData.rotationStyle = Camera::RotationStyle::Linear;
    else if (data->rotationStyle == "EaseInOut")
        configData.rotationStyle = Camera::RotationStyle::EaseInOut;
    else if (data->rotationStyle == "EaseOut")
        configData.rotationStyle = Camera::RotationStyle::EaseOut;

    std::memcpy(configData.cameraRotation.data(), &data->lookForward, sizeof(float) * 6);

    auto& rotations = configData.cameraRotation;

    std::transform(rotations.begin(), rotations.end(), rotations.begin(), [](auto& norm) {
        return RotationConverter::GetRotation(norm);
    });

    configData.experimentalFeatures = data->experimentalFeatures;
    configData.autoCenter = data->autoCenter;
    configData.verticalAngle = data->verticalAngle;

    _cameraController.applyConfig(configData);
}

void SIC::onFrameStart(const hry::FrameStartEvent&& frameEvent)
{
    _isGamePaused = frameEvent.isGamePaused;
    _cameraController.update(frameEvent.deltaTime);
}

void SIC::previewRotationHorizontal(float value)
{
    if (!_isGamePaused)
    {
        _cameraController.getCamera().setRX(RotationConverter::GetRotation(value));
    }
}

void SIC::previewRotationVertical(float value)
{
    if (!_isGamePaused)
    {
        _cameraController.getCamera().setRY(value);
    }
}

void SIC::fillPluginInfo()
{
    _pluginInfo.name = "hry-sic";
    _pluginInfo.fullName = "Smooth Interior Camera";
    _pluginInfo.authorInfo = { "Piotr Krupa", "piotrkrupa06@gmail.com" };
    _pluginInfo.website = "https://hary309.github.io/projects/hry-plugins/hry-sic";
    _pluginInfo.version = { 2, 0, 7 };
    _pluginInfo.desc = R"(
## About
hry-sic improves interior camera by adding smooth rotation animation.
## Changelog
  * 2.0
    * Added UI
    * Added centering vertically
    * Added auto-centering
    * (Probably) fixed stuttering bug with FPS other than 60
    * Dropped x86 (again :(), but you can still use the old version)
                                    )";
}

INIT_PLUGIN(SIC)
