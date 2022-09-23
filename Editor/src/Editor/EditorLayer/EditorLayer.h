#pragma once

#include "Project/Project.h"

using namespace Volund;

class EditorLayer : public Volund::Layer
{
public:

	const Ref<Context> GetContext();

	const Ref<Window> GetWindow();

	const Ref<Scene> GetScene();

	const Ref<Project> GetProject();

	const Ref<RenderingAPI> GetAPI();

	void LoadProject(const std::filesystem::path& Filepath);

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(TimeStep TS) override;

	void OnEvent(Event* E) override;

private:

	Ref<Project> _Project;

	Ref<RenderingAPI> _API;

	Ref<Window> _Window;

	Ref<Context> _Context;
};

