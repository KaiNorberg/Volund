#pragma once

#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Window/Window.h"
#include "AssetManager/AssetManager.h"

namespace Volund
{
	class GameState
	{
	public:

		Ref<Scene> GetScene();

		Ref<AssetManager> GetAssetManager();

		std::string GetScenePath();

		std::string GetParentPath();

		void Procedure(const Event& e);

		GameState(Ref<Scene> scene);

		GameState(const std::string& filepath);

		~GameState();

	private:

		std::string m_ScenePath;

		Ref<Input> m_Input;
		Ref<Scene> m_Scene;
		Ref<AssetManager> m_AssetManager;
	};
}

