#pragma once

#include "Widget/Widget.h"

#include "Project/Project.h"

class Editor : public VL::Application
{
public:

	VL::Ref<VL::Window> GetWindow();

	void OnRun() override;

	void OnTerminate() override;

	void OnUpdate(VL::TimeStep TS) override;

	void OnEvent(VL::Event* E) override;

private:	

	bool BeginDockSpace();

	void Draw(VL::TimeStep TS);

	void DrawMenuBar();

	void DrawProjectMenu();

	void HandleShortcuts();

	bool SetupNeeded();

	void RunSetup();

	VL::Ref<Project> _Project;

	VL::Ref<VL::Window> _Window;

	VL::Ref<VL::Context> _Context;
	
	VL::Container<Widget> _WidgetContainer;

	VL::Input _Input;
};