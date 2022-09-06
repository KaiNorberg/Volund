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

		void LoadScene(Ref<Scene> NewScene);

		void OnAttach() override;

		void OnDetach() override;

		void OnUpdate(TimeStep TS) override;

		void OnEvent(Event* E) override;

	private:

		Ref<Scene> _LoadedScene;
	};
}

