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

		void LoadScene(std::string const& FilePath);

		void OnAttach() override;

		void OnDetach() override;

		void OnUpdate(TimeStep TS) override;

	private:

		Ref<VertexArray> _VertexArray;
		Ref<Shader> _TestShader;
		Ref<Scene> _LoadedScene;
	};
}

