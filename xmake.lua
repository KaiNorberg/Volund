add_rules("mode.debug", "mode.release")
set_license("LGPL-2.0")

add_requires("openal-soft", "glfw", "glad", "lua", "sol2")
set_languages("cxx20");

target("Volund")
    set_kind("shared")
    add_packages("openal-soft", "glfw", "glad", "lua", "sol2")
    add_includedirs("vendor", "src/Volund")
    add_files("src/Volund/*.cpp", "src/Volund/**/*.cpp")

target("ImGui")
    set_kind("static")
    add_cxxflags("-fvisibility=default")
    add_packages("glfw");
    add_includedirs("vendor/imgui", "vendor/glfw/include")
    add_files("vendor/imgui/imgui.cpp")
    add_files("vendor/imgui/imgui_draw.cpp")
    add_files("vendor/imgui/imgui_tables.cpp")
    add_files("vendor/imgui/imgui_widgets.cpp")
    add_files("vendor/imgui/backends/imgui_impl_opengl3.cpp")
    add_files("vendor/imgui/backends/imgui_impl_glfw.cpp")
    add_files("vendor/imgui/misc/cpp/imgui_stdlib.cpp")

target("Editor")
    set_kind("binary")
    add_deps("Volund", "ImGui");
    add_includedirs("src/Volund", "vendor/imgui", "src/Editor")
    add_files("src/Editor/**/*.cpp", "src/Editor/*.cpp")

    after_build(function (target)
        os.cp("data", target:targetdir())
    end)
