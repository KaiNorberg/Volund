#include "PCH/PCH.h"
#include "ForwardRenderer.h"

#include "Frustum/Frustum.h"

namespace Volund
{
	void ForwardRenderer::Begin()
	{
		this->_Data = Data();
	}

	void ForwardRenderer::Submit(const RendererCommand& Command)
	{
		this->_Data.CommandQueue.push_back(Command);
	}

	void ForwardRenderer::Submit(const RendererLight& Light)
	{
		this->_Data.Lights.push_back(Light);
	}

	void ForwardRenderer::Submit(const RendererEye& Eye)
	{
		this->_Data.Eyes.push_back(Eye);
	}

	void ForwardRenderer::End()
	{
		uint32_t LightAmount = (uint32_t)this->_Data.Lights.size();
		this->_LightsUniforms->Set("LightAmount", &LightAmount);
		for (uint64_t i = 0; i < LightAmount; i++)
		{
			Vec3 LightColor = this->_Data.Lights[i].Color * this->_Data.Lights[i].Brightness;
			this->_LightsUniforms->Set("Position" + std::to_string(i), &this->_Data.Lights[i].Position);
			this->_LightsUniforms->Set("Color" + std::to_string(i), &LightColor);
		} 

		this->_CameraUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_CAMERA);
		this->_LightsUniforms->Assign(VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS);

		this->_Data.Sort();

		for (const auto& Eye : this->_Data.Eyes)
		{
			this->_Data.Discriminate(Eye);

			Mat4x4 ViewProjMatrix = Eye.ProjectionMatrix * Eye.ViewMatrix;
			Vec3 EyePosition = Vec3(Eye.ViewMatrix[0][3], Eye.ViewMatrix[1][3], Eye.ViewMatrix[2][3]);
			this->_CameraUniforms->Set("ViewProjMatrix", &ViewProjMatrix);
			this->_CameraUniforms->Set("EyePosition", &EyePosition);

			Ref<Material> PrevMaterial = nullptr;
			for (const auto& Command : this->_Data.CommandQueue)
			{
				if (!Command.Discriminated)
				{
					if (Command.material != PrevMaterial)
					{
						Command.material->UpdateShader();
						PrevMaterial = Command.material;
					}

					Ref<Shader> MaterialShader = Command.material->GetShader();

					if (MaterialShader->HasUniform("_ModelMatrix"))
					{
						MaterialShader->SetMat4x4("_ModelMatrix", Command.ModelMatrix);
					}

					Command.mesh->Bind();
					this->_API->DrawIndexed(Command.mesh);
				}
			}
		}
	}

	ForwardRenderer::ForwardRenderer()
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
}
