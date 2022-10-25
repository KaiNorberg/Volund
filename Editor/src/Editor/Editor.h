#pragma once

#include "Widget/Widget.h"

#include "Project/Project.h"

class Editor : public VL::Application
{
public:

	VL::Ref<VL::Scene> GetScene();

	VL::Ref<Project> GetProject();

	VL::Ref<VL::Window> GetWindow();

	void LoadScene(const std::string& Filepath);

	void OnRun() override;

	void OnTerminate() override;

	void OnUpdate(VL::TimeStep TS) override;

	void OnEvent(VL::Event* E) override;

private:	

	void Draw(VL::TimeStep TS);

	void HandleShortcuts();

	bool BeginDockSpace();

	void DrawMenuBar();

	void DrawProjectMenu();

	VL::Ref<Project> _Project;

	VL::Ref<VL::Scene> _Scene;

	VL::Ref<VL::Window> _Window;

	VL::Ref<VL::Context> _Context;
	
	VL::Container<Widget> _WidgetContainer;

	VL::Input _Input;

	std::string _ScenePath = "";
};