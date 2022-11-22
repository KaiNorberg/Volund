#pragma once

#include "Widget/Widget.h"

#include "Project/Project.h"

class Editor : public VL::Application
{
public:

	VL::Ref<Project> GetProject();

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

	VL::Ref<Project> _Project;
	
	VL::Container<Widget> _WidgetContainer;

	VL::Input _Input;
};