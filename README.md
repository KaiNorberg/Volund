# Volund [![License](https://img.shields.io/badge/licence-MIT-green)](https://github.com/Kaj9296/Volund/blob/main/LICENSE)

Volund is a game engine written in C++ with Lua scripting for Windows and Linux. The game engine supports Lua scripting via an editor, or you can use the engine via a library that allows for native C++ scripting.

***

**Volund is no longer under development and these instructions may be incomplete.**

## Getting Started

To get started with Volund, it is recommended to use Visual Studio 2022 or gmake. Other toolsets may work but are not officially tested. You will need to be using Windows or Linux to build Volund.

<ins>**1. Cloning (downloading) this repository**</ins>

To clone (download) this repository, you can use the ```Code``` button at the top left of the screen, or use the following command if you have git installed ```git clone --recursive https://github.com/Kaj9296/Volund```.

<ins>**2. Building Volund**</ins>

In order to build Volund you will need to have xmake installed on your machine, if you do not have xmake installed you can install it from [here](https://xmake.io/#/).

With xmake installed you can generate the project files using the ```xmake``` command, use ```xmake run``` to launch the editor. 

<!---
## Creating a Scene

In Volund a scene is simply any .lua file. Some example files can be found below and in the [examples](https://github.com/Kaj9296/Volund/tree/main/examples) folder.

## Running a Scene

Currently, the only way to run a scene is to open the Editor (the executable that was generated using your chosen toolset in the previous step) and press ```CTRL + E``` this will open a file dialog from which you can select your desired scene.

## Test Scenes

The following are two of the scenes that can be found in the [examples](https://github.com/Kaj9296/Volund/tree/main/examples) folder.

**Mandelbrot.lua**

![Alt text](resources/Mandelbrot_Screenshot.png "Mandelbrot")

**PBR.lua [WIP]**

![Alt text](resources/Screenshot_PBR.png "PBR")
-->

## Contributing

Volund is open to contributions. There are currently no strict guidelines for contributing, so feel free to submit pull requests that you think are appropriate. If the project grows significantly in the future, a more standardized process for contributions may be implemented.

## Goals:

The main goal of the project is to create a highly versatile game engine that allows for low-level experimentation without the complexity of working on a low level.

- PBR 3D rendering
- Lua scripting
- C++ scripting
- Tools for shader development
- Windows and Linux Compatibility
- Feature complete editor
- Support for multiple graphics APIs for example OpenGL, DirectX, and Vulcan.
