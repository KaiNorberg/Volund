#pragma once

class EditorModule : public VL::Module
{
public:

	VL::Entity SelectedEntity;

	VL::Ref<VL::Scene> GetScene();

	std::string GetSceneFilepath();

	void OnAttach(VL::Application* app) override;

	void OnDetach() override;

	void Procedure(const VL::Event& e) override;

	void SaveScene(const std::string& filepath);

	void LoadNewScene(const std::string& filepath);

private:

	std::mutex m_Mutex;

	VL::Ref<VL::GameState> m_GameState;

	VL::Ref<VL::Window> m_GameWindow;

	std::string m_SceneFilepath;
};

