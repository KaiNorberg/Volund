#include "PCH/PCH.h"
#include "ForwardRenderer.h"

namespace Volund
{
	void ForwardRenderer::Begin(const Mat4x4& ViewMatrix, const Mat4x4& ProjectionMatrix)
	{
		this->_Data = Data();
		this->_Data.ViewMatrix = ViewMatrix;
		this->_Data.ProjectionMatrix = ProjectionMatrix;
	}

	void ForwardRenderer::Submit(const RendererCommand& Command)
	{
		this->_Data.CommandQueue.push_back(Command);
	}

	void ForwardRenderer::Submit(const RendererLight& Light)
	{
		this->_Data.Lights.push_back(Light);
	}

	void ForwardRenderer::End()
	{
		Mat4x4 ViewProjMatrix = this->_Data.ProjectionMatrix * this->_Data.ViewMatrix;
		Vec3 EyePosition = Vec3(this->_Data.ViewMatrix[0][3], this->_Data.ViewMatrix[1][3], this->_Data.ViewMatrix[2][3]);
		this->_CameraUniforms->Set("ViewProjMatrix", &ViewProjMatrix);
		this->_CameraUniforms->Set("EyePosition", &EyePosition);

		uint32_t LightAmount = (uint32_t)this->_Data.Lights.size();
		this->_LightsUniforms->Set("LightAmount", &LightAmount);
		for (uint64_t i = 0; i < LightAmount; i++)
		{
			Vec3 LightColor = this->_Data.Lights[i].Color * this->_Data.Lights[i].Brightness;
			this->_LightsUniforms->Set("Position" + std::to_string(i), &this->_Data.Lights[i].Position);
			this->_LightsUniforms->Set("Color" + std::to_string(i), &LightColor);
		} 

		for (const auto& Command : this->_Data.CommandQueue)
		{
			Command.material->UpdateShader();

			Ref<Shader> MaterialShader = Command.material->GetShader();

			if (MaterialShader->HasUniform("_ModelMatrix"))
			{
				MaterialShader->SetMat4x4("_ModelMatrix", Command.ModelMatrix);
			}

			Command.mesh->Bind();
			this->_API->DrawIndexed(Command.mesh);
		}
	}

	ForwardRenderer::ForwardRenderer()
	{
		this->_CameraUniforms = UniformBuffer::Create();		
		this->_CameraUniforms->PushMatrix<Mat4x4>("ViewProjMatrix");
		this->_CameraUniforms->PushVector<Vec3>("EyePosition");

		this->_CameraUniforms->Allocate(VOLUND_UNIFORM_BUFFER_BINDING_CAMERA);

		this->_LightsUniforms = UniformBuffer::Create();
		this->_LightsUniforms->PushScalar<int>("LightAmount");			
		for (uint64_t i = 0; i < 64; i++)
		{
			this->_LightsUniforms->PushVector<Vec3>("Position" + std::to_string(i));
		}
		for (uint64_t i = 0; i < 64; i++)
		{
			this->_LightsUniforms->PushVector<Vec3>("Color" + std::to_string(i));
		}
		this->_LightsUniforms->Allocate(VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS);
	}
}
