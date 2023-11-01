#include "PCH/PCH.h"
#include "Renderer.h"

#include "Frustum/Frustum.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	void Renderer::Submit(Ref<Scene> scene)
	{
		for (auto& entity : *scene)
		{
			Mat4x4 modelMatrix = Mat4x4();
			Vec3 position = Vec3();
			for (auto& component : entity)
			{
				if (component.Is<Transform>())
				{
					auto transform = component.As<Transform>();

					modelMatrix = transform->GetModelMatrix();
					position = transform->Position;

					break;
				}
			}

			for (auto& component : entity)
			{
				if (component.Is<MeshRenderer>())
				{
					auto meshRenderer = component.As<MeshRenderer>();

					RendererModel model;
					model.LayerMask = meshRenderer->GetLayerMask();
					model.material = meshRenderer->GetMaterial();
					model.mesh = meshRenderer->GetMesh();
					model.ModelMatrix = modelMatrix;

					this->Submit(model);
				}
				else if (component.Is<PointLight>())
				{
					auto pointLight = component.As<PointLight>();

					RendererLight light;
					light.Brightness = pointLight->Brightness;
					light.Color = pointLight->Color;
					light.Position = position;

					this->Submit(light);
				}
				else if (component.Is<Camera>())
				{
					auto camera = component.As<Camera>();

					const auto spec = this->m_Data.Target->GetSpec();
					RendererEye eye;
					eye.LayerMask = camera->GetLayerMask();
					eye.ViewMatrix = camera->GetViewMatrix();
					eye.ProjectionMatrix = camera->GetProjectionMatrix((float)spec.Width / (float)spec.Height);
					eye.Target = nullptr; //TODO: Implement render cameras
					this->Submit(eye);
				}
			}
		}
	}

	void Renderer::Submit(Ref<GameState> gameState)
	{
		this->Submit(gameState->GetScene());
	}

	void Renderer::Submit(const RendererModel& model)
	{
		this->m_Data.Models.push_back(model);
	}

	void Renderer::Submit(const RendererLight& light)
	{
		this->m_Data.Lights.push_back(light);
	}

	void Renderer::Submit(const RendererEye& eye)
	{
		this->m_Data.Eyes.push_back(eye);
	}
}
