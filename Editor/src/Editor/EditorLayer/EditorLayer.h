#pragma once

using namespace Volund;

class EditorLayer : public Volund::Layer
{
public:

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	Ref<Window> _Window;

	Ref<Context> _Context;

	Ref<Scene> _Scene;

	bool PlayScene;
};

