#pragma once

#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Window/Window.h"
#include "Filesystem/Filesystem.h"

namespace Volund
{
	class GameState
	{
	public:

		Ref<Scene> GetScene();

		void Procedure(const Event& e);

		GameState(Ref<Window> window, const std::string& filepath);

		~GameState();

	private:

		Ref<Input> m_Input;
		Ref<Scene> m_Scene;
		Ref<FilesystemLink> m_FilesystemLink;
	};
}

