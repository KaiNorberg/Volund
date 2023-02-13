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

	buildoptions 
	{ 
		"/bigobj" 
	}

	dependson 
	{
		"ImGui",
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
		"vendor/GLAD/include",
		"vendor/imgui",
		"vendor/lua"
	}

	libdirs
	{
		TargetDir,
		"vendor/lua",
		"vendor/OpenAL_Soft/lib"
	}
	
	links
	{
		"OpenGL32.lib",
		"OpenAL32.lib",
		"common.lib",
		"ex-common.lib",
		"Glad.lib",
		"ImGui",
		"lua54",
		"winmm"
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
		optimize "Speed"
		runtime "Release"

	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "Speed"
		runtime "Release"	
		
project "Editor"
	location "Editor"
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

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor",
		"vendor/imgui",
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
		kind "ConsoleApp"

	filter "configurations:Release"
		defines "VOLUND_RELEASE"
		optimize "Speed"
		runtime "Release"
		kind "ConsoleApp"

	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "Speed"
		runtime "Release"	
		kind "WindowedApp"		
		targetdir (TargetDir .. "\\Editor")
		postbuildcommands {
			"xcopy data\\* ..\\" .. TargetDir .. "\\Editor\\data /Q /E /Y /I /S"
		}
		
project "Glad"
	kind "StaticLib"
	language "C"
	location "vendor/glad"
	cppdialect "C++20"

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
		optimize "Speed"

project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++20"

	location "vendor/imgui"

	targetdir (TargetDir)
	objdir (ObjDir)

	includedirs
	{
		"vendor/imgui"
	}

	files
	{
		"vendor/imgui/imconfig.h",
		"vendor/imgui/imgui.h",
		"vendor/imgui/imgui.cpp",
		"vendor/imgui/imgui_draw.cpp",
		"vendor/imgui/imgui_internal.h",
		"vendor/imgui/imgui_tables.cpp",
		"vendor/imgui/imgui_widgets.cpp",
		"vendor/imgui/imstb_rectpack.h",
		"vendor/imgui/imstb_textedit.h",
		"vendor/imgui/backends/imgui_impl_opengl3.cpp",
		"vendor/imgui/backends/imgui_impl_opengl3.h",
		"vendor/imgui/backends/imgui_impl_win32.cpp",
		"vendor/imgui/backends/imgui_impl_win32.h",
		"vendor/imgui/misc/cpp/imgui_stdlib.cpp",
		"vendor/imgui/misc/cpp/imgui_stdlib.h"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
        symbols "off"