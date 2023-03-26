#pragma once

#include "../Module.h"

#include "GameState/GameState.h"

namespace Volund
{
	class GameModule : public Module
	{
	public:

		void OnAttach(Application* app) override;

		void OnDetach() override;

		void Procedure(const Event& e) override;

		std::string GetFilepath();

		Ref<Scene> GetScene();

		void NewState(const std::string& filepath);

	private:	

		std::mutex m_Mutex;

		Ref<GameState> m_GameState;

		Ref<Window> m_GameWindow;

		std::string m_Filepath;
	};
}