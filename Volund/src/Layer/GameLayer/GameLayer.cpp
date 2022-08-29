#include "PCH/PCH.h"

#include "GameLayer.h"

#include "Renderer/Renderer.h"

#include "Component/Camera/Camera.h"

namespace Volund
{
	void GameLayer::OnAttach()
	{

	}

	void GameLayer::OnDetach()
	{

	}

	void GameLayer::OnUpdate(TimeStep TS)
	{
		Camera* ActiveCamera = Camera::GetActiveCamera();

		if (ActiveCamera != nullptr)
		{
			Renderer::BeginScene(ActiveCamera);

			if (_LoadedScene != nullptr)
			{
				this->_LoadedScene->Update(TS);
			}

			Renderer::EndScene();
		}
		else
		{
			if (_LoadedScene != nullptr)
			{
				this->_LoadedScene->Update(TS);
			}
		}
	}

	void GameLayer::OnEvent(Event* E)
	{
		if (_LoadedScene != nullptr)
		{
			this->_LoadedScene->EventCallback(E);
		}
	}
}