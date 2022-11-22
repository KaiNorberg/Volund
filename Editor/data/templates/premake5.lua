workspace "VOLUND_PROJECT_NAME"
architecture "x64"

configurations
{
	"Debug",
	"Release",
	"Dist"
}

TargetDir = "bin\\%{cfg.buildcfg}_x64"
ObjDir = "bin\\Intermediate\\%{cfg.buildcfg}_x64\\%{prj.name}"

project "VOLUND_PROJECT_NAME"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"
	staticruntime "on"

	targetdir (TargetDir)
	objdir (ObjDir)

	files
	{

	}

	includedirs
	{
		"src",
		"vendor",
	}

	libdirs
	{
		TargetDir
	}

	links
	{
		"Volund",
		"OpenGL32.lib",
		"Glad.lib"
	}

	filter "configurations:Debug"
		defines "VOLUND_DEBUG"
		symbols "On"
		runtime "Debug"
		kind "ConsoleApp"

	filter "configurations:Release"
		defines "VOLUND_RELEASE"
		optimize "On"
		runtime "Release"
		kind "ConsoleApp"

	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "On"
		runtime "Release"	
		kind "WindowedApp"