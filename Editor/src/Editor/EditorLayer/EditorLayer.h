#pragma once

using namespace Volund;

class EditorLayer : public Volund::Layer
{
public:

	Ref<Window> GetWindow();

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	Ref<Window> _Window;

	Ref<Context> _Context;

	Ref<Scene> _Scene;
};

