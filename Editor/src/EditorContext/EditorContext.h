#pragma once

class EditorContext : public VL::Module
{
public:

	VL::Entity SelectedEntity = 1;

	void OnAttach(VL::Application* app) override;

	void OnDetach() override;

	void Procedure(const VL::Event& e) override;

	std::string GetFilepath();

	VL::Ref<VL::Scene> GetScene();

	VL::Ref<VL::Window> GetWindow();

	void LoadScene(const std::string& filepath);

	void SaveScene(const std::string& filepath);

private:		
	
	std::mutex m_Mutex;

	VL::Ref<VL::GameState> m_GameState;

	VL::Ref<VL::Window> m_GameWindow;

	std::string m_Filepath;
};

