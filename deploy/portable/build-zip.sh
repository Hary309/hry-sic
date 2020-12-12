#!/bin/bash
rm -rf hry-sic.zip
rm -rf plugins
mkdir -p plugins plugins/hry_plugins plugins/hry_assets
cp -f ../../build/hry-sic.dll plugins/hry_plugins/hry-sic.dll
cp -f ../../vendor/hry-core/bin/release/hry-core.dll plugins/hry-core.dll
cp -rf ../../vendor/hry-core/assets/* plugins/hry_assets
7z a hry-sic.zip plugins/*