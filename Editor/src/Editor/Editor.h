#pragma once

#include "Project/Project.h"

class UI;

using namespace Volund;

class Editor : public Volund::Application
{
public:

	const Ref<Context> GetContext();

	const Ref<Window> GetWindow();

	void OnRun() override;

	void OnTerminate() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:	
	
	Ref<Project> _Project;

	Ref<Window> _Window;

	Ref<Context> _Context;

	Ref<UI> _UI;
};