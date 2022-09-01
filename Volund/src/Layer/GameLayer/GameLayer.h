#pragma once

#include "Layer/Layer.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Shader/Shader.h"
#include "Scene/Scene.h"

namespace Volund
{
	class GameLayer : public Layer
	{
	public:

		template<typename T>
		void LoadScene();

		void OnAttach() override;

		void OnDetach() override;

		void OnUpdate(TimeStep TS) override;

		void OnEvent(Event* E) override;

	private:

		Ref<Scene> _LoadedScene;
	};

	template<typename T>
	inline void GameLayer::LoadScene()
	{
		VOLUND_INFO("Loading Scene...");

		this->_LoadedScene.reset(new T());
	}
}

