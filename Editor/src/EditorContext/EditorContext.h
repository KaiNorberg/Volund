#pragma once

class Editor;

class EditorContext
{
public:

	VL::Entity SelectedEntity = 1;

	VL::Ref<VL::Window> GetWindow();

	VL::Ref<VL::Scene> GetScene();

	std::string GetSceneFilepath();

	void SaveScene(const std::string& filepath);

	void LoadNewScene(const std::string& filepath);

	EditorContext(VL::Ref<VL::Window> window);

private:
	friend class Editor;

	std::mutex m_Mutex;

	VL::Ref<VL::GameState> m_State;

	VL::Ref<VL::Window> m_Window;

	std::string m_SceneFilepath;
};

