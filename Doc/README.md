# Naruto Senki - V2

- [Naruto Senki - V2](#naruto-senki---v2)
  - [Introduction](#introduction)
    - [What have I done?](#what-have-i-done)
    - [What is the next?](#what-is-the-next)
  - [Know Issues](#know-issues)
  - [TODO](#todo)
  - [How to build?](#how-to-build)
    - [Adnroid](#adnroid)
    - [Linux](#linux)
    - [Windows](#windows)
  - [Structure](#structure)
  - [How to develop?](#how-to-develop)
  - [What is NarutoSenki: Re?](#what-is-narutosenki-re)

---

> For More details visit [game.naruto.re](https://game.naruto.re)
>
> Based on NarutoSenki source code

Get the latest developments👇
- Telegram: [t.me/narutosenki_re](https://t.me/narutosenki_re)
- Discord: [discord.gg/JGA6P8p](https://discord.gg/JGA6P8p)
- Youtube: [Re Offical Channel](https://www.youtube.com/channel/UCL9gDeedGZdf3hjRd-Zr7cg)

## Introduction

> Full desktop preview on [here](https://youtu.be/AaHkA1RmXxkg)

> `NOTE: This project will no longer develop after a few months`

### What have I done?

- **UPDATED**
  - Updated the project to cocos2d-x 2.2.6 & Visual Studio 2019
  - Most dependent libraries have been upgraded to the latest version
  - Updated glfw2 to glfw3
  - [Adnroid] Support android 11.0 and rounded icons
  - [Adnroid] Support android arm64-v8a
  - [Linux] Use OpenAL instead of FMod
  - [Windows] Use OpenAL instead of native music player
  - [Assets] Use `ogg` format instead of `mp3`
  - Upgrade LuaJit to git master（Updated luajit android build script）
  - Added old characters Orochimaru/Pain/Kimimaro (No AI Support)
- **FIXED**
  - Correct wrong words && Use english word instead of some chinese variables
  - Combined `NetworkLayer` and `SelectLayer` to `SelectLayer`
  - Separated a few of highly coupled code (All in `Core` folder)
  - Make some not core UI classes implemented by lua
  - [Config] Added some not existed sound files (`HokageMinato_xxx`, etc...)
  - [Gameplay] Fixed character spawn on the wrong direction when the character is right team `Akatsuki`
  - [Gameplay] Fixed character will flip when player only move up or down
  - [Gameplay] Fixed sometimes you can't move when you touched a tower (It still exist)
  - [Android] Fixed battle not fluent
  - [Windows] Fixed high CPU usage (It happened on low cocos2d-x version)
  - [UI] Extended map background
  - [UI] Fullscreen menu background
  - [UI] Make a new battle UI for Desktop platform
- **REMOVED**
  - Click logo will not affect the game
  - All network codes & dependence (websocket)
  - [Config] Removed `Hidan` & `Kakuzu` & `Chiyo` hurt sound (It doesn't existed)
- **FEATURES**
  - Click `NETWORK` button to enable custom select character
  - [Linux & Windows] Half keyboard supported (Only working on battle scene)

### What is the next?

> I dont't want this project to take up more of my time.
>
> So I will back to the main work ---
> continue develop [NarutoSenki: Re](#what-is-narutosenki-re)
>
> I may continue to develop this project if I want.

## Know Issues

- All
  - Map black lines
- Windows
  - You tell me !
- Linux
  - The `Text Component` manifested are incomplete.
- Android
  - Some sounds will not playing when the battle starts in the first few seconds.
  - May not be fluent on your android device when you select a character. (Caused by the `Select` module implemented by lua)
  - I didn't compile a x64 lua-jit for android, so we can't be build x64 version or you can remove the dependence on `scripting/lua/proj.android/Android.mk`
  - Menu's notice clipper not working on android. (But it works great on the other platforms)

## TODO

- Support shortcut switch from `windowed` to `fullscreen` and more
- Use `grpc + protobuf` develop local multiplayer
- Use `OpenAL` play music on `android` platform (May be fixed sounds not wordking)
- Full keyboard support

---

## How to build?

### Adnroid

Open `project/NarutoSenki/proj.android` with Android Studio

Press `Ctrl + F9` to make project

### Linux

dependence:
  - Arch
    > `pacman -Syu freetype gcc glfw gtk3 openal openal-alut pthread sqlite3`

    or you can also use yay

    > `yay -Syu `

``` bash
git clone https://github.com/real-re/NarutoSenki-V2
cd NarutoSenki-V2
./build.sh
```
or
``` bash
cd NarutoSenki-V2
cd tools/tolua++
make
cd ../../
make # DEBUG=1 # -j12
```

### Windows

- Open `cocos2d-win32.sln` with Visual Studio 2019

or

- Run `build.bat` and `build-win32.bat`

## Structure

```
root: projects/NarutoSenki

├───Classes
│   ├───Core
│   │   ├───Bullet
│   │   ├───Guardian
│   │   ├───Kuchiyose
│   │   ├───Scripts
│   │   ├───Shinobi
│   │   │   └───Bunshin
│   │   ├───Tower
│   │   └───Warrior
│   └───MyUtils
├───lua
│   ├───class
│   ├───core
│   ├───framework
│   │   └───cocos2dx
│   ├───ui
│   └───utils
├───proj.android-studio
├───proj.ios
├───proj.linux
├───proj.mac
├───proj.win32
├───Resources
│   ├───Audio
│   ├───Effects
│   ├───Element
│   ├───Fonts
│   └───Tiles
├───sprites
└───__BIN__
```

- Meaning
  - Classes : C++ source files
    - Core
      - Bullet
      - Guardian
      - Kuchiyose
      - Scripts
      - Shinobi
        - Bunshin
    - MyUtils
  - lua : Lua script files
  - proj.android-studio : Android project
  - proj.ios : IOS project (Not support)
  - proj.linux : Linux project
  - proj.mac : MAC project (Not support)
  - proj.win32 : Windows project
  - Resources
  - sprites : Unused assets
  - \_\_BIN__ : Build output (Linux & Windows)

## How to develop?

- Tools
  - [TexturePacker](https://www.codeandweb.com/texturepacker)
  - [TextureUnpacker](https://github.com/real-re/TextureUnpacker)
    - Batch split textures that made by TexturePacker
  - [Tiled](https://www.mapeditor.org/)
    - Can create maps (Get more rules open `xxx.tmx` in `projects/NarutoSenki/Resources/Tiles/` with tiled)

## What is NarutoSenki: Re?

> Made with Unity3D and still in development naruto video game.
>
> For now, looks like it's just NarutoSenki developed with another game engine.

You can get all the notices at the above `telegram` or `discord`.

---

**<font color=#D32F2F>M</font><font color=#FF5722>a</font><font color=#FFEB3B>d</font><font color=#8BC34A>e</font> <font color=#00BCD4>b</font><font color=#448AFF>y</font> <font color=#673AB7>R</font><font color=#FF4081>e</font>**
