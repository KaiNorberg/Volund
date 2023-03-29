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
		"ImGui",
		"Glad",
		"GLFW"
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
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/imgui",
		"vendor/lua"
	}

	libdirs
	{
		TargetDir,
		"vendor/lua",
		"vendor/OpenAL_Soft/lib"
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

	filter "system:windows" 
		links
		{
			"OpenGL32",
			"Glad",
			"GLFW",
			"OpenAL32",
			"common",
			"ex-common",
			"ImGui",
			"lua54",
			"winmm"
		}
	filter "system:linux" 
		links
		{
			"dl",
			"Glad",
			"GLFW",
			"openal",
			"common",
			"ex-common",
			"ImGui",
			"lua54",
		}
		
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
		"Volund/src",
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/lua"
	}

	libdirs
	{
		TargetDir,
		"vendor/lua",
		"vendor/OpenAL_Soft/lib"
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

	filter "system:windows" 
		postbuildcommands {
			"xcopy data\\* ..\\" .. TargetDir .. "\\data /Q /E /Y /I /S"
		}
		links
		{
			"Volund",
			"OpenGL32",
			"Glad",
			"GLFW",
			"OpenAL32",
			"common",
			"ex-common",
			"ImGui",
			"lua54",
			"winmm"
		}
	filter "system:linux" 
		postbuildcommands {
			"cp -R data ../bin/%{cfg.buildcfg}_x64"
		}
		links
		{
			"Volund",
			"dl",
			"Glad",
			"GLFW",
			"openal",
			"common",
			"ex-common",
			"ImGui",
			"lua54",
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
		"vendor/glad/include"
	}

	files
	{
		"vendor/glad/include/glad/glad.h",
		"vendor/glad/include/KHR/khrplatform.h",
		"vendor/glad/src/glad.c"
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
		"vendor/imgui",
		"vendor/glfw/include"
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
		"vendor/imgui/backends/imgui_impl_glfw.cpp",
		"vendor/imgui/backends/imgui_impl_glfw.h",
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

project "GLFW"
	kind "StaticLib"
	language "C"
	location "vendor/glfw"

	targetdir (TargetDir)
	objdir (ObjDir)
	
	systemversion "latest"
	staticruntime "on"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
		symbols "off"

	filter "system:windows" 
		defines 
		{ 
			"GLFW_VULKAN_STATIC",
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

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

	filter "system:linux" 
		defines 
		{ 
			"GLFW_VULKAN_STATIC",
			"_GLFW_X11",
			"_CRT_SECURE_NO_WARNINGS"
		}

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

			"vendor/glfw/src/posix_module.c",
			"vendor/glfw/src/posix_poll.c",
			"vendor/glfw/src/posix_thread.c",
			"vendor/glfw/src/posix_time.c",

			"vendor/glfw/src/linux_joystick.c",

			"vendor/glfw/src/x11_init.c",
			"vendor/glfw/src/x11_monitor.c",
			"vendor/glfw/src/x11_window.c",

			"vendor/glfw/src/glx_context.c",
			"vendor/glfw/src/egl_context.c",
			"vendor/glfw/src/xkb_unicode.c",
			"vendor/glfw/src/osmesa_context.c"
		}
