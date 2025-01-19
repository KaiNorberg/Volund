#include "Rendering/Renderer.h"

#include "Frustum.h"

#include "Component/Components.h"

namespace Volund
{
	void Renderer::Submit(std::shared_ptr<Scene> scene, std::shared_ptr<Framebuffer> target)
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
					position = transform->pos;

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
					light.Brightness = pointLight->brightness;
					light.Color = pointLight->color;
					light.pos = position;

					this->Submit(light);
				}
				else if (component.Is<Camera>())
				{
					auto camera = component.As<Camera>();

					const auto spec = target->GetSpec();
					RendererEye eye;
					eye.LayerMask = camera->GetLayerMask();
					eye.ViewMatrix = camera->GetViewMatrix();
					eye.ProjectionMatrix = camera->GetProjectionMatrix((float)spec.Width / (float)spec.Height);
					eye.Target = target;
					this->Submit(eye);
				}
			}
		}
	}

	void Renderer::Submit(const RendererModel& model)
	{
		this->m_data.Models.push_back(model);
	}

	void Renderer::Submit(const RendererLight& light)
	{
		this->m_data.Lights.push_back(light);
	}

	void Renderer::Submit(const RendererEye& eye)
	{
		this->m_data.Eyes.push_back(eye);
	}
}