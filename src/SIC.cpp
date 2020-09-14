#include "SIC.hpp"

SIC::Result SIC::init(const SIC::InitParams&& initParams)
{
    if (!hry::IsApiCompatible(initParams.apiVersion))
    {
        return SIC::Result::ApiNotSupported;
    }

    Logger = initParams.logger;

    return SIC::Result::Ok;
}

void SIC::initConfig(hry::Config* /*config*/)
{
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

INIT_PLUGIN(SIC)
