#pragma once

#include "Hry/Plugin.hpp"

class SIC : public hry::Plugin
{
private:
    hry::PluginInfo _pluginInfo{ "hry-sic",
                                 "Smooth Interior Camera",
                                 { "Piotr Krupa", "piotrkrupa06@gmail.com" },
                                 "TODO",
                                 hry::Version{ 2, 0, 0 } };

public:
    inline static hry::Logger* Logger;

public:
    Result init(const InitParams&& initParams) override;

    void initConfig(hry::Config* config) override;

    void initKeyBinds(hry::KeyBinds* keyBinds) override;

    void initEvents(hry::EventHandler* eventHandler) override;

    // replace with manifest.json
    const hry::PluginInfo& getPluginInfo() const override;
};
