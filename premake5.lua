workspace "Volund"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.architecture}"

project "Volund"
	location "Volund"
	kind "SharedLib"
	language "C++"

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
		"vendor"
	}

	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"
	
	defines
	{
		"VOLUND_BUILD_DLL"
	}

	pchheader "PCH/PCH.h"
	pchsource "%{prj.name}/src/PCH/PCH.cpp"

	filter "configurations:Debug"
		defines "VOLUND_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VOLUND_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "On"

project "Engine"
	location "Engine"
	kind "ConsoleApp"
	language "C++"

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

	links
	{
		"Volund"
	}

	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	filter "configurations:Debug"
		defines "VOLUND_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VOLUND_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "On"