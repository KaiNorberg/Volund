#pragma once

#include "Widget/Widget.h"

#include "Project/Project.h"

class Editor;

class UI
{
public:

	VL::Ref<VL::Window> GetWindow();

	VL::Ref<Project> GetProject();

	void Draw(VL::TimeStep TS);

	void OnEvent(VL::Event* E);

	UI(VL::Ref<VL::Window> Window, VL::Ref<Project> Project);

	~UI();

private:

	void HandleShortcuts();

	void BeginDockSpace();

	void DrawMenuBar();

	void DrawProjectMenu();

	void DrawSceneMenu();

	VL::Ref<VL::Window> _Window;

	VL::Ref<Project> _Project;

	VL::Container<Widget> _WidgetContainer;

	VL::Input _Input;
};

