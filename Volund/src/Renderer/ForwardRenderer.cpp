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
		for (const auto& Command : this->_Data.CommandQueue)
		{
			Command.material->UpdateShader();

			Ref<Shader> MaterialShader = Command.material->GetShader();

			if (MaterialShader->HasUniform("_ModelMatrix"))
			{
				MaterialShader->SetMat4x4("_ModelMatrix", Command.ModelMatrix);
			}

			if (MaterialShader->HasUniform("_EyePosition"))
			{
				Vec3 EyePosition = Vec3(this->_Data.ViewMatrix[0][3], this->_Data.ViewMatrix[1][3], this->_Data.ViewMatrix[2][3]);
				MaterialShader->SetVec3("_EyePosition", EyePosition);
			}

			if (MaterialShader->HasUniform("_ViewProjMatrix"))
			{
				MaterialShader->SetMat4x4("_ViewProjMatrix", this->_Data.ProjectionMatrix * this->_Data.ViewMatrix);
			}

			if (MaterialShader->HasUniform("_PointLights[0].Color"))
			{
				MaterialShader->SetInt("_PointLightAmount", this->_Data.Lights.size());

				for (uint64_t i = 0; i < this->_Data.Lights.size(); i++)
				{
					std::string Uniform = "_PointLights[" + std::to_string(i) + "].";
					MaterialShader->SetVec3(Uniform + "Color", this->_Data.Lights[i].Color);
					MaterialShader->SetFloat(Uniform + "Brightness", this->_Data.Lights[i].Brightness);
					MaterialShader->SetVec3(Uniform + "Position", this->_Data.Lights[i].Position);
				}
			}

			Command.mesh->Bind();
			this->_API->DrawIndexed(Command.mesh);
		}
	}
}
