#pragma once

#include "Layer/Layer.h"

#include "Renderer/VertexArray/VertexArray.h"
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

	private:

		Ref<VertexArray> _VertexArray;
		Ref<Shader> _TestShader;
		Ref<Scene> _LoadedScene;
	};

	template<typename T>
	inline void GameLayer::LoadScene()
	{
		VOLUND_INFO("Loading Scene ...");

		this->_LoadedScene.reset(new T());
	}
}

