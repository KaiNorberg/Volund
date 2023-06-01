#pragma once

#ifdef VOLUND_DIST
	#define MAIN_SCENE "scene.lua"
#else
	#define MAIN_SCENE "../examples/Simple/scene.lua"
#endif

class Launcher : public VL::Application
{
public:

	void Procedure(const VL::Event& e) override;

	Launcher();

private:
};

