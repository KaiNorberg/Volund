#pragma once

#include "../Module.h"

#include "GameState/GameState.h"

#include "Rendering/Renderer/ForwardRenderer/ForwardRenderer.h"

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

		Ref<Window> GetWindow();

		void LoadScene(const std::string& filepath);

	private:	

		std::mutex m_Mutex;

		Ref<GameState> m_GameState;

		Ref<Window> m_GameWindow;

		Ref<Renderer> m_Renderer;

		Ref<Framebuffer> m_Framebuffer;

		std::string m_Filepath;
	};
}