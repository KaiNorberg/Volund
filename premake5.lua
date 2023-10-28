---@diagnostic disable: undefined-global
workspace "Volund"
	architecture "x64"

	configurations { "Debug", "Release", "Dist" }

TargetDir = "bin\\%{cfg.buildcfg}_x64"
ObjDir = "bin\\Intermediate\\%{cfg.buildcfg}_x64\\%{prj.name}"

project "Volund"
	location "Volund"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	targetdir (TargetDir)
	objdir (ObjDir)

	dependson { "ImGui", "Glad", "GLFW" }

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src", "vendor", "vendor/imgui" }
	libdirs { TargetDir, "vendor" }
	
	defines { "VOLUND_CORE" }

	pchheader "PCH/PCH.h"
	pchsource "%{prj.name}/src/PCH/PCH.cpp"

	filter "system:windows" 
		links
		{
			TargetDir .. "/Glad",
			TargetDir .. "/GLFW",
			TargetDir .. "/ImGui",
			"OpenGL32",
			"winmm",
			"vendor/OpenAL_Soft/lib/OpenAL32",
			"vendor/OpenAL_Soft/lib/common",
			"vendor/OpenAL_Soft/lib/ex-common",
			"vendor/lua/lua54",
		}
	filter "system:linux" 
		links 
		{		

		}

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
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	targetdir (TargetDir)
	objdir (ObjDir)

	dependson { "Volund" }

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src", "vendor", "vendor/imgui", "Volund/src" }
	libdirs { TargetDir, "vendor", "vendor/OpenAL_Soft/lib", "vendor/lua/" }

	pchheader "PCH/PCH.h"
	pchsource "%{prj.name}/src/PCH/PCH.cpp"

	filter "system:windows" 
		links
		{
			"Volund"
		}
	filter "system:linux" 
		links 
		{ 
			"Volund",	
			"dl",
			"Glad",
			"GLFW",
			"ImGui",
			"openal",
			"common",
			"ex-common",
			"lua54",
		}

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

project "Launcher"
	location "Launcher"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	targetdir (TargetDir)
	objdir (ObjDir)

	dependson { "Volund" }

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src", "vendor", "vendor/imgui", "Volund/src" }
	libdirs { TargetDir, "vendor", "vendor/OpenAL_Soft/lib", "vendor/lua/" }

	pchheader "PCH/PCH.h"
	pchsource "%{prj.name}/src/PCH/PCH.cpp"

	filter "system:windows" 
		links
		{
			"Volund"
		}
	filter "system:linux" 
		links 
		{ 
			"Volund",	
			"dl",
			"Glad",
			"GLFW",
			"ImGui",
			"openal",
			"common",
			"ex-common",
			"lua54",
		}

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
		
project "Glad"
	location "vendor/glad"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	targetdir (TargetDir)
	objdir (ObjDir)

	files
	{
		"vendor/glad/include/glad/glad.h",
		"vendor/glad/include/KHR/khrplatform.h",
		"vendor/glad/src/glad.c"
	}

	includedirs { "%{prj.name}/src", "vendor", "vendor/glad/include" }
	libdirs { TargetDir, "vendor" }

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
		
project "ImGui"
	location "vendor/imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	targetdir (TargetDir)
	objdir (ObjDir)

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

	includedirs { "%{prj.name}/src", "vendor/imgui", "vendor/glfw/include" }
	libdirs { TargetDir, "vendor" }

	--filter "system:linux"
		--pic "On"

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

project "GLFW"
	location "vendor/glfw"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	targetdir (TargetDir)
	objdir (ObjDir)
	
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

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
