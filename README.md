# Volund [![License](https://img.shields.io/badge/licence-MIT-green)](https://github.com/Kaj9296/Volund/blob/main/LICENSE)


Volund is a game engine written in C++ with Lua scripting for the Windows 10/11 operating system.

***

## Getting Started

Visual Studio 2019/2022 is recommended since any other tool sets are not officially tested however, you are welcome to try and use any other tool sets should you wish. Windows 10/11 will be required to build Volund.

<ins>**1. Cloning (downloading) this repository**</ins>

Cloning this repository can either be done via the green ```Code``` button at the top of the screen or if you have git installed the following command ```git clone --recursive https://github.com/Kaj9296/Volund```.

<ins>**2. Building Volund**</ins>

Building Volund is as simple as running the [premake.bat](https://github.com/Kaj9296/Volund-2/blob/main/premake.bat) file in the CMD with an argument specifying what toolset you wish to use. For example, if you wish to use Visual Studio 2022 then you would type ```premake.bat vs2022```.

After that, you can simply compile the generated project with your chosen tool set!

## Goals:

- PBR 3D rendering
- 3rd party 3D physics engine
- Audio system
- Lua scripting
- A feature-complete Entity Component system
- Support for multiple graphics APIs for example OpenGL, DirectX and Vulcan
