workspace "Volund"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}_x64"

project "Volund"
	location "Volund"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	dependson 
	{
		"GLFW",
		"Glad"
	}

	targetdir ("bin/" .. outputdir)
	objdir ("bin/" .. outputdir .. "/%{prj.name}_int")

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
		("bin/" .. outputdir)
	}
	
	links
	{
		"OpenGL32.lib",
		"GLFW.lib",
		"Glad.lib"
	}

	cppdialect "C++20"
	systemversion "latest"
	
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

project "Engine"
	location "Engine"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	dependson 
	{
		"Volund"
	}

	targetdir ("bin/" .. outputdir)
	objdir ("bin/" .. outputdir .. "/%{prj.name}_int")

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
		("bin/" .. outputdir)
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

	cppdialect "C++20"
	systemversion "latest"

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

project "GLFW"
	kind "StaticLib"
	language "C"
	location "vendor/glfw"

	targetdir ("bin/" .. outputdir)
	objdir ("bin/" .. outputdir .. "/%{prj.name}_int")


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
	
	systemversion "latest"
	staticruntime "on"

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

	targetdir ("bin/" .. outputdir)
	objdir ("bin/" .. outputdir .. "/%{prj.name}_int")

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
