#pragma once

#include "Widget/Widget.h"

using namespace Volund;

class UILayer : public Volund::Layer
{
public:

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	std::string OpenFileDialog();

	void BeginDockSpace();

	Container<Widget> _WidgetContainer;
};

