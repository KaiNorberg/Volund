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
			auto componentRegistry = entity.second;

			Mat4x4 modelMatrix = Mat4x4();
			Vec3 position = Vec3();
			if (componentRegistry.Contains<Transform>())
			{
				auto transform = componentRegistry.Get<Transform>();

				modelMatrix = transform->GetModelMatrix();
				position = transform->Position;
			}

			for (int i = 0; i < componentRegistry.Size<MeshRenderer>(); i++)
			{
				auto meshRenderer = componentRegistry.Get<MeshRenderer>(i);

				RendererModel model;
				model.LayerMask = meshRenderer->GetLayerMask();
				model.material = meshRenderer->GetMaterial();
				model.mesh = meshRenderer->GetMesh();
				model.ModelMatrix = modelMatrix;

				this->Submit(model);
			}

			for (int i = 0; i < componentRegistry.Size<Camera>(); i++)
			{
				auto camera = componentRegistry.Get<Camera>(i);

				RendererEye eye;
				eye.LayerMask = camera->GetLayerMask();
				eye.Position = position;
				eye.ViewMatrix = camera->GetViewMatrix();
				eye.Target = camera->GetTargetBuffer();

				float aspectRatio;
				if (eye.Target == nullptr)
				{
					const auto spec = this->m_Data.DefaultBuffer->GetSpec();
					aspectRatio = (float)spec.Width / (float)spec.Height;
				}
				else
				{
					const auto spec = eye.Target->GetSpec();
					aspectRatio = (float)spec.Width / (float)spec.Height;
				}
				
				eye.ProjectionMatrix = camera->GetProjectionMatrix(aspectRatio);

				this->Submit(eye);
			}

			for (int i = 0; i < componentRegistry.Size<PointLight>(); i++)
			{
				auto pointLight = componentRegistry.Get<PointLight>(i);

				RendererLight light;
				light.Brightness = pointLight->Brightness;
				light.Color = pointLight->Color;
				light.Position = position;

				this->Submit(light);
			}
		}
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

	Renderer::Renderer()
	{
		this->m_CameraUniforms = UniformBuffer::Create();
		this->m_CameraUniforms->PushMatrix<Mat4x4>("ViewProjMatrix");
		this->m_CameraUniforms->PushVector<Vec3>("EyePosition");
		this->m_CameraUniforms->Allocate();

		this->m_LightsUniforms = UniformBuffer::Create();
		this->m_LightsUniforms->PushScalar<int>("LightAmount");
		for (uint64_t i = 0; i < VOLUND_MAX_LIGHTS; i++)
		{
			this->m_LightsUniforms->PushVector<Vec3>("Position" + std::to_string(i));
		}
		for (uint64_t i = 0; i < VOLUND_MAX_LIGHTS; i++)
		{
			this->m_LightsUniforms->PushVector<Vec3>("Color" + std::to_string(i));
		}
		this->m_LightsUniforms->Allocate();
	}

	void Renderer::UpdateLightUniforms()
	{
		VOLUND_PROFILE_FUNCTION();

		uint32_t lightAmount = (uint32_t)this->m_Data.Lights.size();
		
		if (lightAmount > VOLUND_MAX_LIGHTS)
		{
			lightAmount = 64;
		}

		this->m_LightsUniforms->Set("LightAmount", &lightAmount);
		for (uint64_t i = 0; i < lightAmount; i++)
		{
			Vec3 lightColor = this->m_Data.Lights[i].Color * this->m_Data.Lights[i].Brightness;
			this->m_LightsUniforms->Set("Position" + std::to_string(i), &this->m_Data.Lights[i].Position);
			this->m_LightsUniforms->Set("Color" + std::to_string(i), &lightColor);
		}

		this->m_LightsUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS);
	}

	void Renderer::UpdateCameraUniforms(const RendererEye& eye)
	{
		VOLUND_PROFILE_FUNCTION();

		const Mat4x4 viewProjMatrix = eye.ProjectionMatrix * eye.ViewMatrix;
		this->m_CameraUniforms->Set("ViewProjMatrix", &viewProjMatrix);
		this->m_CameraUniforms->Set("EyePosition", &eye.Position);

		this->m_CameraUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_CAMERA);
	}

	void Renderer::Data::Sort()
	{
		VOLUND_PROFILE_FUNCTION();

		std::sort(this->Models.begin(), this->Models.end(), [](const RendererModel& a, const RendererModel& b)
		{
			return a.material < b.material;
		});
	}

	void Renderer::Data::Discriminate(const RendererEye& eye)
	{
		VOLUND_PROFILE_FUNCTION();

		const Frustum cameraFrustum(eye.ProjectionMatrix * eye.ViewMatrix);

		for (auto& model : this->Models)
		{
			bool isInFrustum = model.mesh != nullptr && cameraFrustum.ContainsAABB(model.mesh->GetAABB(model.ModelMatrix));
			bool isInMask = (model.LayerMask & eye.LayerMask) != 0;

			model.Discriminated = !isInFrustum || !isInMask;
		}
	}
}
