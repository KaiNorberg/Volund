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
		targetdir (TargetDir .. "/Volund")
		postbuildcommands {			
			"xcopy ..\\vendor\\glm\\** ..\\" .. TargetDir .. "\\Volund\\vendor\\glm /Q /E /Y /I /S",
			"xcopy ..\\vendor\\json\\** ..\\" .. TargetDir .. "\\Volund\\vendor\\json /Q /E /Y /I /S",
			"xcopy src\\**.h ..\\" .. TargetDir .. "\\Volund\\include /Q /E /Y /I /S"
		}
		
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
		targetdir (TargetDir .. "/Editor")
		postbuildcommands {
			"xcopy Data\\* ..\\" .. TargetDir .. "\\Editor /Q /E /Y /I /S"
		}
		
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
