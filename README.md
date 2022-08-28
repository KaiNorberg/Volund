# Volund [![License](https://img.shields.io/badge/licence-MIT-green)](https://github.com/Kaj9296/Volund-2/LICENCE)


Volund is an OpenGL rendering engine designed for Windows 10/11.

***

## Getting Started

Visual Studio 2019/2022 is recommended since any other tool sets are not officially tested however, you are welcome to try and use any other tool sets should you wish. Windows 10/11 will be required to build Volund.

<ins>**1. Cloning (downloading) this repository**</ins>

Cloning this repository can either be done via the green ```Code``` button at the top of the screen or if you have git installed the following command ```git clone --recursive https://github.com/Kaj9296/Volund```.

<ins>**2. Building Volund**</ins>

Building Volund is as simple as running the [premake.bat](https://github.com/Kaj9296/Volund-2/blob/main/premake.bat) file in the CMD with an argument specifying what toolset you wish to use. For example, if you wish to use Visual Studio 2022 then you would type ```premake.bat vs2022```.

After that, you can simply compile the generated project with your chosen tool set!

## Goals:

The main goal for Volund is to create a versatile application capable of being used for anything from making games to a 3D physics simulation. The hope is to achieve this versatility while maintaining ease of use and performance.

- PBR 3D rendering
- 3rd party 3D physics engine
- Audio 
- C++ and C# scripting
- Fully editable JSON files for storing all information about a scene
- A feature-complete designer/editor
