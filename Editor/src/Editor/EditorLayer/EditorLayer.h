#pragma once

using namespace Volund;

class EditorLayer : public Volund::Layer
{
public:

	Ref<Window> GetWindow();

	void LoadScene(const std::filesystem::path& FilePath);

	void LoadProject(const std::filesystem::path& FilePath);

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	VML _CurrentProject;

	Ref<Scene> _CurrentScene;

	Ref<RenderingAPI> _API;

	Ref<Window> _Window;

	Ref<Context> _Context;
};

