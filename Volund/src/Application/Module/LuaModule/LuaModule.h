#pragma once

#include "../Module.h"

#include "Core/Lua/LuaState/LuaState.h"

namespace Volund
{
	class LuaModule : public Module
	{
	public:

		std::string GetFilepath();

		Ref<Scene> GetScene();

		void LoadScene(const std::string& Filepath);

		void OnEvent(Event* E) override;

		void OnRender() override;

		void OnUpdate(TimeStep TS) override;

		void OnAttach(Application* App) override;

		void OnDestroy() override;

	private:	

		Ref<LuaState> _LuaState;

		Application* _App = nullptr;

		std::string _Filepath;
	};
}