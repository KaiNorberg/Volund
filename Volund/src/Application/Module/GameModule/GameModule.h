#pragma once

#include "../Module.h"

#include "GameState/GameState.h"

namespace Volund
{
	class GameModule : public Module
	{
	public:

		void OnAttach(Application* App) override;

		void OnDetach() override;

		void Procedure(const Event& E) override;

		std::string GetFilepath();

		Ref<Scene> GetScene();

		void NewState(const std::string& Filepath);

	private:	

		std::mutex _Mutex;

		Ref<GameState> _GameState;

		Ref<Window> _GameWindow;

		std::string _Filepath;
	};
}