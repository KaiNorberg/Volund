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

	void BeginDockSpace();

	void DrawMenuBar();

	std::string OpenFileDialog(const std::wstring& Title, const std::wstring& Extension);

	Container<Widget> _WidgetContainer;
};

