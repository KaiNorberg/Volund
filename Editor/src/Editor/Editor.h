#pragma once

#include "Widget/Widget.h"

class Editor : public VL::Application
{
public:

	void OnRun() override;

	void OnTerminate() override;

	void OnUpdate(VL::TimeStep TS) override;

	void OnRender() override;

	void OnEvent(VL::Event* E) override;

private:
	
	std::vector<VL::Ref<Widget>> _Widgets;

	VL::Input _Input;
};