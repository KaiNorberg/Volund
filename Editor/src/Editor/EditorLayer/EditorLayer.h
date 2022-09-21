#pragma once

using namespace Volund;

class EditorLayer : public Volund::Layer
{
public:

	const Ref<Context> GetContext();

	const Ref<Window> GetWindow();

	const Ref<Scene> GetScene();

	const Ref<VML> GetProject();

	const Ref<RenderingAPI> GetAPI();

	void SaveScene(const std::filesystem::path& FilePath);

	void LoadScene(const std::filesystem::path& FilePath);

	void LoadProject(const std::filesystem::path& FilePath);

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	Ref<VML> _Project;

	Ref<Scene> _Scene;

	Ref<RenderingAPI> _API;

	Ref<Window> _Window;

	Ref<Context> _Context;
};

