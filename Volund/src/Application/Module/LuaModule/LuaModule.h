#pragma once

#include "../Module.h"

#include "Lua/LuaState/LuaState.h"

namespace Volund
{
	class LuaModule : public Module
	{
	public:

		void OnAttach(Application* App) override;

		void OnDetach() override;

		void Procedure(const Event& E) override;

		std::string GetFilepath();

		Ref<Scene> GetScene();

		void LoadScene(const std::string& Filepath);

	private:	

		std::mutex _Mutex;

		Ref<LuaState> _LuaState;

		Application* _App = nullptr;

		std::string _Filepath;
	};
}