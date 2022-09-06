#include "PCH/PCH.h"

#include "GameLayer.h"

#include "Renderer/Renderer.h"

#include "Component/Camera/Camera.h"
#include "Component/Transform/Transform.h"
#include "Component/PointLight/PointLight.h"

namespace Volund
{
	void GameLayer::LoadScene(Ref<Scene> NewScene)
	{
		this->_LoadedScene = NewScene;
	}

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
			Mat4x4 ViewProjMatrix = ActiveCamera->GetProjectionMatrix() * ActiveCamera->GetViewMatrix();
			Vec3 EyePosition = ActiveCamera->GetEntity()->GetComponent<Transform>()->Position;

			auto const& PointLightView = this->_LoadedScene->ComponentView<PointLight>();
			std::vector<PointLightData> PointLights;
			PointLights.reserve(PointLightView.size());
			for (auto const& Light : PointLightView)
			{
				PointLights.push_back({Light->Color, Light->GetEntity()->GetComponent<Transform>()->Position});
			}

			Renderer::BeginScene(ViewProjMatrix, EyePosition, PointLights);

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