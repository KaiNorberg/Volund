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
			"xcopy src\\**.h ..\\" .. TargetDir .. "\\Volund\\include /Q /E /Y /I /S"
		}
		
project "Editor"
	location "Editor"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"
	staticruntime "on"

	dependson 
	{
		"Volund",
		"ImGui"
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
		"Editor/vendor/imgui",
		"Volund/src"
	}

	libdirs
	{
		TargetDir
	}

	links
	{
		"Volund",
		"ImGui",
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
		optimize "On"
		runtime "Release"
		kind "ConsoleApp"

	filter "configurations:Dist"
		defines "VOLUND_DIST"
		optimize "On"
		runtime "Release"	
		kind "WindowedApp"
		targetdir (TargetDir .. "/Editor")
		postbuildcommands {
			"xcopy Standard\\* ..\\" .. TargetDir .. "\\Editor\\Standard /Q /E /Y /I /S"
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
		optimize "on"

project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++20"

	location "Editor/vendor/imgui"

	targetdir (TargetDir)
	objdir (ObjDir)

	includedirs
	{
		"Editor/vendor/imgui"
	}

	files
	{
		"Editor/vendor/imgui/imconfig.h",
		"Editor/vendor/imgui/imgui.h",
		"Editor/vendor/imgui/imgui.cpp",
		"Editor/vendor/imgui/imgui_draw.cpp",
		"Editor/vendor/imgui/imgui_internal.h",
		"Editor/vendor/imgui/imgui_tables.cpp",
		"Editor/vendor/imgui/imgui_widgets.cpp",
		"Editor/vendor/imgui/imstb_rectpack.h",
		"Editor/vendor/imgui/imstb_textedit.h",
		"Editor/vendor/imgui/backends/imgui_impl_opengl3.cpp",
		"Editor/vendor/imgui/backends/imgui_impl_opengl3.h",
		"Editor/vendor/imgui/backends/imgui_impl_win32.cpp",
		"Editor/vendor/imgui/backends/imgui_impl_win32.h"
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
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"