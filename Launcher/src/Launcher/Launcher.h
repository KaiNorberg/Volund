#pragma once

#ifdef VOLUND_DIST
	#define MAIN_SCENE "scene.lua"
#else
	#define MAIN_SCENE "../examples/Mandelbrot/scene.lua"
#endif

class Launcher : public VL::Application
{
public:

	void Procedure(const VL::Event& e) override;

	Launcher();

private:

	VL::Ref<VL::Framebuffer> m_Framebuffer;
	VL::Ref<VL::Renderer> m_Renderer;
	VL::Ref<VL::GameState> m_GameState;
};

