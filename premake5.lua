workspace "Volund"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

TargetDir = "bin\\%{cfg.buildcfg}_x64"
ObjDir = "bin\\Intermediate\\%{cfg.buildcfg}_x64\\%{prj.name}"

project "Volund"
	location "Volund"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"
	staticruntime "on"

	dependson 
	{
		"GLFW",
		"Glad"
	}

	targetdir (TargetDir)
	objdir (ObjDir)

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor",
		"vendor/GLAD/include"
	}

	libdirs
	{
		TargetDir
	}
	
	links
	{
		"OpenGL32.lib",
		"GLFW.lib",
		"Glad.lib"
	}
	
	defines
	{
		"VOLUND_CORE"
	}

	pchheader "PCH/PCH.h"
	pchsource "%{prj.name}/src/PCH/PCH.cpp"

	filter "configurations:Debug"
		defines "VOLUND_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "VOLUND_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "On"
		runtime "Release"

project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"
	staticruntime "on"

	dependson 
	{
		"Volund"
	}

	targetdir (TargetDir)
	objdir (ObjDir)
	debugdir "%{prj.name}/Data"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor",
		"Volund/src"
	}

	libdirs
	{
		TargetDir
	}

	links
	{
		"Volund",
		"OpenGL32.lib",
		"GLFW.lib",
		"Glad.lib"
	}
		
	pchheader "PCH/PCH.h"
	pchsource "%{prj.name}/src/PCH/PCH.cpp"

	filter "configurations:Debug"
		defines "VOLUND_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "VOLUND_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "On"
		runtime "Release"
		postbuildcommands {
		  "xcopy Data\\ ..\\" .. TargetDir .. "\\ /E /C /Y"
		}

project "GLFW"
	kind "StaticLib"
	language "C"
	location "vendor/glfw"
	systemversion "latest"
	staticruntime "on"

	targetdir (TargetDir)
	objdir (ObjDir)

	files
	{
		"vendor/glfw/include/GLFW/glfw3.h",
		"vendor/glfw/include/GLFW/glfw3native.h",
		"vendor/glfw/src/glfw_config.h",
		"vendor/glfw/src/context.c",
		"vendor/glfw/src/init.c",
		"vendor/glfw/src/input.c",
		"vendor/glfw/src/monitor.c",

		"vendor/glfw/src/null_init.c",
		"vendor/glfw/src/null_joystick.c",
		"vendor/glfw/src/null_monitor.c",
		"vendor/glfw/src/null_window.c",

		"vendor/glfw/src/platform.c",
		"vendor/glfw/src/vulkan.c",
		"vendor/glfw/src/window.c",
		"vendor/glfw/src/win32_init.c",
		"vendor/glfw/src/win32_joystick.c",
		"vendor/glfw/src/win32_module.c",
		"vendor/glfw/src/win32_monitor.c",
		"vendor/glfw/src/win32_time.c",
		"vendor/glfw/src/win32_thread.c",
		"vendor/glfw/src/win32_window.c",
		"vendor/glfw/src/wgl_context.c",
		"vendor/glfw/src/egl_context.c",
		"vendor/glfw/src/osmesa_context.c"
	}

	defines 
	{ 
		"GLFW_VULKAN_STATIC",
		"_GLFW_WIN32",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "Glad"
	kind "StaticLib"
	language "C"
	location "vendor/glad"

	targetdir (TargetDir)
	objdir (ObjDir)

	includedirs
	{
		"vendor/GLAD/include"
	}

	files
	{
		"vendor/GLAD/include/glad/glad.h",
		"vendor/GLAD/include/KHR/khrplatform.h",
		"vendor/GLAD/src/glad.c"
	}
	
	systemversion "latest"
	staticruntime "on"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
