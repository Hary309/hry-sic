#include "SIC.hpp"

#include <string>

#include <Hry/Config/Fields/BoolField.hpp>
#include <Hry/Config/Fields/NumericField.hpp>
#include <Hry/Config/Fields/SelectionField.hpp>

#include "Hooks/CameraHook.hpp"

#include "ConfigData.hpp"


struct InternalConfigData
{
    float speed{};
    std::string rotationStyle;
    bool centerVertically;
    float cameraPosition[6];
};

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
                    .useCombo()
                    .build());

    config->add(hry::BoolFieldBuilder()
                    .setID("center_vertically")
                    .setLabel("Center vertically")
                    .setDefaultValue(true)
                    .bind(&InternalConfigData::centerVertically)
                    .build());
}

void SIC::initKeyBinds(hry::KeyBinds* /*keyBinds*/)
{
}

void SIC::initEvents(hry::EventHandler* event)
{
    event->game.onFrameStart.connect<&SIC::onFrameStart>(this);
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

    _cameraController.applyConfig(configData);
}

void SIC::onFrameStart(const hry::FrameEvent&& frameEvent)
{
    _cameraController.update(frameEvent.deltaTime);
}

INIT_PLUGIN(SIC)
