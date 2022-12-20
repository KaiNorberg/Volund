#include "PCH/PCH.h"
#include "ForwardRenderer.h"

#include "Frustum/Frustum.h"

namespace Volund
{
	void ForwardRenderer::Begin()
	{
		uint64_t OldCommandSize = this->_Data.CommandQueue.size();

		this->_Data = Data();
		this->_Data.CommandQueue.reserve(OldCommandSize);
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
		this->_Data.Sort();

		this->UpdateLightUniforms();

		for (const auto& Eye : this->_Data.Eyes)
		{
			this->_Data.Discriminate(Eye);

			this->UpdateCameraUniforms(Eye);

			Eye.Target->Bind();

			auto& TargetSpec = Eye.Target->GetSpec();

			VL::RenderingAPI::Clear();						
			VL::RenderingAPI::SetViewPort(0, 0, (int32_t)TargetSpec.Width, (int32_t)TargetSpec.Height);

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

					if (MaterialShader->HasUniform(VOLUND_UNIFORM_NAME_MODELMATRIX))
					{
						MaterialShader->SetMat4x4(VOLUND_UNIFORM_NAME_MODELMATRIX, Command.ModelMatrix);
					}

					Command.mesh->Bind();
					this->_API->DrawIndexed(Command.mesh);
				}
			}

			Eye.Target->Unbind();
		}
	}
}
