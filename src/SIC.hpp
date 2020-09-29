#pragma once

#include <Hry/Config/Fields/NumericField.hpp>
#include <Hry/Plugin.hpp>

#include "CameraController.hpp"
#include "ConfigData.hpp"
#include "DefaultRotations.hpp"
#include "RotationConverter.hpp"

class SIC : public hry::Plugin
{
private:
    hry::PluginInfo _pluginInfo{};

    CameraController _cameraController;

    bool _isGamePaused = true;

public:
    inline static hry::Logger* Logger;

public:
    SIC();

    Result init(const InitParams&& initParams) override;

    void initConfig(hry::Config* config) override;

    void initKeyBinds(hry::KeyBinds* keyBinds) override;

    void initEvents(hry::EventHandler* eventHandler) override;

    // replace with manifest.json
    const hry::PluginInfo& getPluginInfo() const override;

private:
    void onConfigChangesApplied(const hry::ConfigCallbackData& callbackData);
    void onFrameStart(const hry::FrameStartEvent&& frameEvent);

    template<typename ValueType, typename ClassType>
    void addRotationField(
        hry::Config* config,
        const char* id,
        const char* label,
        Camera::Position position,
        ValueType ClassType::*member)
    {
        const auto defaultRotation = DefaultRotations::GetRotation(position);
        const auto normalizedRotation = RotationConverter::GetNormalized(defaultRotation);

        config->add(hry::NumericFieldBuilder<float>()
                        .setID(id)
                        .setLabel(label)
                        .bind(member)
                        .setDefaultValue(normalizedRotation)
                        .useSlider(-1.f, 1.f, "%.2f")
                        .setPreviewCallback(hry::Dlg<&SIC::previewRotationHorizontal>(this))
                        .build());
    }

    template<Camera::Position Position>
    void addRotationKeybind(
        hry::KeyBinds* keyBinds, const char* id, const char* label, hry::BindableKey::Key_t key)
    {
        keyBinds->add(
            hry::KeyBindBuilder()
                .setID(id)
                .setLabel(label)
                .setDescription(
                    "This keybind works only when 'Experimental features' in settings is enabled")
                .setDefaultKey(key)
                .setActivator(hry::KeyBind::Activator::Click)
                .setPressCallback({ [](void* data, hry::ButtonState /**/) {
                                       auto* self = reinterpret_cast<SIC*>(data);
                                       self->_cameraController.onKeyBindPress(Position);
                                   },
                                    this })
                .setReleaseCallback({ [](void* data, hry::ButtonState /**/) {
                                         auto* self = reinterpret_cast<SIC*>(data);
                                         self->_cameraController.onKeyBindRelease(Position);
                                     },
                                      this })
                .build());
    }

    void previewRotationHorizontal(float value);
    void previewRotationVertical(float value);
};
