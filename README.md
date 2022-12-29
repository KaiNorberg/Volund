# Volund [![License](https://img.shields.io/badge/licence-MIT-green)](https://github.com/Kaj9296/Volund/blob/main/LICENSE)


Volund is a game engine written in C++ with Lua scripting for the Windows 10/11 operating system.

***

**Keep in mind that Volund is currently in a very early stage of development and that these instructions may be incomplete.**

## Getting Started

To get started with Volund, it is recommended to use Visual Studio 2019 or 2022. Other tool sets may work, but are not officially tested. You will need to be using Windows 10/11 to build Volund.

<ins>**1. Cloning (downloading) this repository**</ins>

To clone (download) this repository, you can use the ```Code``` button at the top left of the screen, or use the following command if you have git installed ```git clone --recursive https://github.com/Kaj9296/Volund```.

<ins>**2. Building Volund**</ins>

Building Volund is as simple as running the [premake.bat](https://github.com/Kaj9296/Volund-2/blob/main/premake.bat) file in the CMD with an argument specifying what toolset you wish to use. For example, if you wish to use Visual Studio 2022 then you would type ```premake.bat vs2022```.

After that, you can simply compile the generated project with your chosen tool set!

## Running a Scene

In Volund a scene is simply any .lua file. Currently the only way to run a scene is to open the Editor and click the ```Load Scene``` button within the ```Viewport``` Widget, after that simply select the .lua file you wish to run.

## Example Scene

```java

SimpleShader = Shader:new("Simple.vshader")

RedMaterial = Material:new(SimpleShader)
RedMaterial:SetVec3("Color", Vec3:new(1.0, 0.0, 0.0))

CubeMesh = Mesh:new("Cube.vobj")

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 2.0, 10.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})

RedCube = Scene:CreateEntity()
RedCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.0)})
RedCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = RedMaterial})

PointLight = Scene:CreateEntity()
PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 5.0, 5.0)})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)})
```

There are more examples provided in the [TestScenes](https://github.com/Kaj9296/Volund/tree/main/TestScenes) folder, you may also go to the [Wiki](https://github.com/Kaj9296/Volund/wiki) for more documentation on the lua API.

## Contributing

Volund is open to contributions. There are currently no strict guidelines for contributing, so feel free to submit pull requests that you think are appropriate. If the project grows significantly in the future, a more standardized process for contributions may be implemented.

## Goals:

The main goal of the project is to create a game engine that allows for low level experimentation without the complexity of working on a low level.

- PBR 3D rendering
- 3rd party 3D physics engine
- Audio system
- Lua scripting
- A feature-complete Entity Component system.
- Support for multiple graphics APIs for example OpenGL, DirectX and Vulcan.
- Tools for training and using deep learning/neural networks.
