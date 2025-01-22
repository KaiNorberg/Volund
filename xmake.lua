add_rules("mode.debug", "mode.release")
set_license("LGPL-2.0")

add_requires("openal-soft", "glfw", "glad", "lua", "sol2", "stb", "imgui v1.89.5-docking", {configs = {
    docking = true,
    glfw = true,
    opengl3 = true
}})
set_languages("cxx20")

target("Volund")
    set_kind("shared")
    add_defines("VOLUND_BUILD")
    add_packages("openal-soft", "glfw", "glad", "lua", "sol2", "stb")
    add_includedirs("include", "vendor", "include/Volund")
    add_files("src/Volund/*.cpp", "src/Volund/**/*.cpp")

target("Editor")
    set_kind("binary")
    add_deps("Volund")
    add_packages("openal-soft", "glfw", "sol2", "imgui")
    add_includedirs("include", "vendor", "src/Editor")
    add_files("src/Editor/**/*.cpp", "src/Editor/*.cpp")
    -- Add imgui backend files explicitly if they're in your project
    add_files("vendor/imgui_backends/imgui_impl_glfw.cpp")
    add_files("vendor/imgui_backends/imgui_impl_opengl3.cpp")

    after_build(function (target)
        os.cp("data", target:targetdir())
    end)