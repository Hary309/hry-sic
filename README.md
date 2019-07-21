# Smooth Interior Camera

[![Downloads](https://img.shields.io/github/downloads/Harry09/Smooth-Interior-Camera/total.svg?label=downloads&logo=GitHub)](https://github.com/Harry09/Smooth-Interior-Camera/releases)
[![GitHub release](https://img.shields.io/github/release/Harry09/Smooth-Interior-Camera.svg)](https://github.com/Harry09/Smooth-Interior-Camera/releases/tag/1.3.1.0)
[![Support via PayPal](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme2/PiotrKrupa)

Camera mod for ETS 2 and ATS. Best experience with vsync and stable 60 fps

## Video

[![Image](http://img.youtube.com/vi/M6WYAOJAsMQ/0.jpg)](http://www.youtube.com/watch?v=M6WYAOJAsMQ)

## [Download](https://github.com/Harry09/Smooth-Interior-Camera/releases)

## Features

- Smooth camera rotation
- Three types of animation ([Linear](https://www.youtube.com/watch?v=10TyElHZJc4), [EaseInOut](https://www.youtube.com/watch?v=M6WYAOJAsMQ), [EaseOut](https://www.youtube.com/watch?v=WQA5rA-Rqqo))
- Universal for every keys settings (default is for numpad)
- Possibility to change predefined camera positions

## Hotkeys

- **INSERT** - enable/disable mod
- **DELETE** - change predefined positions of camera
- **HOME** - reload settings from file

## How to install

### For 64 bit

1. Go to **ets 2** or **ats** directory
1. Then to `bin/win_x64`
1. Here create `plugins` folder
1. Copy **sic_x64.dll** to `plugins` folder
1. Run game in **x64** mode

### For 32 bit

1. Go to **ets 2** directory
1. Then to `bin/win_x86`
1. Here create `plugins` folder
1. Copy **sic_x86.dll** to `plugins` folder
1. Run game in **x86** mode

## How to change predefined camera position

1. Press **Delete**
1. Set the position of the camera (with mouse)
1. Press key which you want look here

## How to develop

1. Git clone and submodules init

```bash
git clone https://github.com/Harry09/Smooth-Interior-Camera.git
cd Smooth-Interior-Camera
git submodule init
git submodule update --recursive
```

2. Open project `src/Smooth Interior Camera.sln`
