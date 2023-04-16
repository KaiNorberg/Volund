#pragma once

class EditorModule : public VL::Module
{
public:

	VL::Entity SelectedEntity;

	VL::Ref<VL::Scene> GetScene();

	std::string GetFilepath();

	void OnAttach(VL::Application* app) override;

	void OnDetach() override;

	void Procedure(const VL::Event& e) override;

	void LoadNewState(const std::string& filepath);

private:

	std::mutex m_Mutex;

	VL::Ref<VL::GameState> m_GameState;

	VL::Ref<VL::Window> m_GameWindow;

	std::string m_Filepath;
};

