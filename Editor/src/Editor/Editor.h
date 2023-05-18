#pragma once

#include "Widget/Widget.h"

class Editor : public VL::Application
{
public:

	void OnRun() override;

	void OnTerminate() override;

	void Procedure(const VL::Event& e) override;

	virtual ~Editor() = default;

private:
	std::vector<VL::Ref<Widget>> m_Widgets;

	VL::Input m_Input;
};