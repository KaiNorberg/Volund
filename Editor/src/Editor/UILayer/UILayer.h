#pragma once

#include "Widget/Widget.h"

using namespace Volund;

class UILayer : public Volund::Layer
{
public:

	std::string GetSelectedEntity();

	void SetSelectedEntity(const std::string& NewEntity);

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	void BeginDockSpace();

	void DrawMenuBar();

	void DrawProjectMenu();

	void DrawSceneMenu();

	Container<Widget> _WidgetContainer;

	std::string _SelectedEntity;
};

