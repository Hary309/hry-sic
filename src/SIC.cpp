#include "SIC.hpp"

#include "Hry/Config/Fields/NumericField.hpp"
#include "Hry/Config/Fields/SelectionField.hpp"

#include "ConfigData.hpp"

struct InternalConfigData
{
    float speed{};
    std::string rotationStyle;
    float cameraPosition[6];
};

SIC::Result SIC::init(const SIC::InitParams&& initParams)
{
    if (!hry::IsApiCompatible(initParams.apiVersion))
    {
        return SIC::Result::ApiNotSupported;
    }

    Logger = initParams.logger;

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
                    .setDefaultValue(0.75f)
                    .build());

    config->add(hry::SelectionFieldBuilder()
                    .setID("rotation_style")
                    .setLabel("Rotation style")
                    .addOptions("Linear", "EaseInOut", "EaseOut")
                    .setDefaultValue("EaseInOut")
                    .useCombo()
                    .build());
}

void SIC::initKeyBinds(hry::KeyBinds* /*keyBinds*/)
{
}

void SIC::initEvents(hry::EventHandler* /*eventHandler*/)
{
}

const hry::PluginInfo& SIC::getPluginInfo() const
{
    return _pluginInfo;
}

void SIC::onConfigChangesApplied(const hry::ConfigCallbackData& callbackData)
{
    auto* data = callbackData.getData<InternalConfigData>();
    _configData.speed = data->speed;

    if (data->rotationStyle == "Linear")
        _configData.rotationStyle = Camera::Linear;
    else if (data->rotationStyle == "EaseInOut")
        _configData.rotationStyle = Camera::EaseInOut;
    else if (data->rotationStyle == "EaseOut")
        _configData.rotationStyle = Camera::EaseOut;
}

INIT_PLUGIN(SIC)
