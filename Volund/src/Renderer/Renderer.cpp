#include "PCH/PCH.h"
#include "Renderer.h"

#include "Frustum/Frustum.h"

namespace Volund
{
	void RendererInstance::Submit(const RendererModel& model)
	{
		this->m_Data.Models.push_back(model);
	}

	void RendererInstance::Submit(const RendererLight& light)
	{
		this->m_Data.Lights.push_back(light);
	}

	void RendererInstance::Submit(const RendererEye& eye)
	{
		this->m_Data.Eyes.push_back(eye);
	}

	void RendererInstance::Init()
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

	void RendererInstance::UpdateLightUniforms()
	{
		VOLUND_PROFILE_FUNCTION();

		const uint32_t lightAmount = (uint32_t)this->m_Data.Lights.size();
		this->m_LightsUniforms->Set("LightAmount", &lightAmount);
		for (uint64_t i = 0; i < lightAmount; i++)
		{
			Vec3 lightColor = this->m_Data.Lights[i].Color * this->m_Data.Lights[i].Brightness;
			this->m_LightsUniforms->Set("Position" + std::to_string(i), &this->m_Data.Lights[i].Position);
			this->m_LightsUniforms->Set("Color" + std::to_string(i), &lightColor);
		}

		this->m_LightsUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS);
	}

	void RendererInstance::UpdateCameraUniforms(const RendererEye& eye)
	{
		VOLUND_PROFILE_FUNCTION();

		const Mat4x4 viewProjMatrix = eye.ProjectionMatrix * eye.ViewMatrix;
		this->m_CameraUniforms->Set("ViewProjMatrix", &viewProjMatrix);
		this->m_CameraUniforms->Set("EyePosition", &eye.Position);

		this->m_CameraUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_CAMERA);
	}

	void RendererInstance::Data::Sort()
	{
		VOLUND_PROFILE_FUNCTION();

		std::sort(this->Models.begin(), this->Models.end(), [](const RendererModel& a, const RendererModel& b)
		{
			return a.material < b.material;
		});
	}

	void RendererInstance::Data::Discriminate(const RendererEye& eye)
	{
		VOLUND_PROFILE_FUNCTION();

		const Frustum cameraFrustum(eye.ProjectionMatrix * eye.ViewMatrix);

		for (auto& model : this->Models)
		{
			model.Discriminated = !cameraFrustum.ContainsAABB(model.mesh->GetAABB(model.ModelMatrix)) || ((model.LayerMask & eye.LayerMask) == 0);
		}
	}

	void Renderer::Init(const Ref<RendererInstance> instance)
	{
		m_Instance = instance;
		m_Instance->Init();
	}

	void Renderer::Reset()
	{
		m_Instance.reset();
	}

	void Renderer::Begin()
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->Begin();
	}

	void Renderer::Submit(const RendererModel& model)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->Submit(model);
	}

	void Renderer::Submit(const RendererLight& light)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->Submit(light);
	}

	void Renderer::Submit(const RendererEye& eye)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->Submit(eye);
	}

	void Renderer::End()
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->End();
	}
}
