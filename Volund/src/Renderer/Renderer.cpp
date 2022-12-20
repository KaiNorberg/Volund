#include "PCH/PCH.h"
#include "Renderer.h"

#include "Frustum/Frustum.h"

namespace Volund
{
	RendererInstance::RendererInstance()
	{
		this->_CameraUniforms = UniformBuffer::Create();
		this->_CameraUniforms->PushMatrix<Mat4x4>("ViewProjMatrix");
		this->_CameraUniforms->PushVector<Vec3>("EyePosition");
		this->_CameraUniforms->Allocate();

		this->_LightsUniforms = UniformBuffer::Create();
		this->_LightsUniforms->PushScalar<int>("LightAmount");
		for (uint64_t i = 0; i < VOLUND_MAX_LIGHTS; i++)
		{
			this->_LightsUniforms->PushVector<Vec3>("Position" + std::to_string(i));
		}
		for (uint64_t i = 0; i < VOLUND_MAX_LIGHTS; i++)
		{
			this->_LightsUniforms->PushVector<Vec3>("Color" + std::to_string(i));
		}
		this->_LightsUniforms->Allocate();
	}

	void RendererInstance::UpdateLightUniforms()
	{
		VOLUND_PROFILE_FUNCTION();

		uint32_t LightAmount = (uint32_t)this->_Data.Lights.size();
		this->_LightsUniforms->Set("LightAmount", &LightAmount);
		for (uint64_t i = 0; i < LightAmount; i++)
		{
			Vec3 LightColor = this->_Data.Lights[i].Color * this->_Data.Lights[i].Brightness;
			this->_LightsUniforms->Set("Position" + std::to_string(i), &this->_Data.Lights[i].Position);
			this->_LightsUniforms->Set("Color" + std::to_string(i), &LightColor);
		}

		this->_LightsUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS);
	}

	void RendererInstance::UpdateCameraUniforms(const RendererEye& Eye)
	{
		VOLUND_PROFILE_FUNCTION();

		Mat4x4 ViewProjMatrix = Eye.ProjectionMatrix * Eye.ViewMatrix;
		Vec3 EyePosition = Vec3(Eye.ViewMatrix[0][3], Eye.ViewMatrix[1][3], Eye.ViewMatrix[2][3]);
		this->_CameraUniforms->Set("ViewProjMatrix", &ViewProjMatrix);
		this->_CameraUniforms->Set("EyePosition", &EyePosition);		
		
		this->_CameraUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_CAMERA);
	}

	void RendererInstance::Data::Sort()
	{
		VOLUND_PROFILE_FUNCTION();

		std::sort(this->CommandQueue.begin(), this->CommandQueue.end(), [](const RendererCommand& A, const RendererCommand& B)
		{
			return A.material < B.material;
		});
	}

	void RendererInstance::Data::Discriminate(const RendererEye& Eye)
	{
		VOLUND_PROFILE_FUNCTION();

		Frustum CameraFrustum(Eye.ProjectionMatrix * Eye.ViewMatrix);

		for (auto& Command : this->CommandQueue)
		{
			Command.Discriminated = !CameraFrustum.ContainsAABB(Command.mesh->GetAABB(Command.ModelMatrix));
		}
	}

	void Renderer::Init(const Ref<RendererInstance>& Instance)
	{
		_Instance = Instance;
	}

	void Renderer::Init(RendererInstance* Instance)
	{
		_Instance = Ref<RendererInstance>(Instance);
	}

	void Renderer::Reset()
	{
		_Instance.reset();
	}

	void Renderer::Begin()
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->Begin();
	}

	void Renderer::Submit(const RendererCommand& Command)
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->Submit(Command);
	}

	void Renderer::Submit(const RendererLight& Light)
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->Submit(Light);
	}

	void Renderer::Submit(const RendererEye& Eye)
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->Submit(Eye);
	}

	void Renderer::End()
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->End();
	}
}
