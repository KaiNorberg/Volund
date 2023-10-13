#pragma once

#define EDITOR_EVENT_TYPE_LOAD_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 1)
#define EDITOR_EVENT_TYPE_RELOAD_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 2)
#define EDITOR_EVENT_TYPE_SAVE_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 3)
#define EDITOR_EVENT_TYPE_NEW_SCENE (VOLUND_HIGHEST_EVENT_TYPE + 4)
#define EDITOR_EVENT_TYPE_RESET (VOLUND_HIGHEST_EVENT_TYPE + 5)

class EditorContext : public VL::Module
{
public:

	VL::Entity SelectedEntity = 1;

	void OnAttach(VL::Application* app) override;

	void OnDetach() override;

	void Procedure(const VL::Event& e) override;

	bool IsPaused();

	void Play();

	void Pause();

	VL::Ref<VL::AssetManager> GetAssetmanager();

	VL::Ref<VL::Scene> GetScene();

	VL::Ref<VL::Window> GetWindow();

private:	

	void LoadScene(const std::string& filepath);

	void SaveScene(const std::string& filepath);

	bool m_Paused = true;

	std::mutex m_Mutex;

	VL::Ref<VL::Dispatcher> m_Dispatcher;

	VL::Ref<VL::GameState> m_GameState;

	VL::Ref<VL::Window> m_GameWindow;
};

