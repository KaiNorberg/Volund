#include "PCH/PCH.h"
#include "ForwardRenderer.h"

#include "Frustum/Frustum.h"

namespace Volund
{
	void ForwardRenderer::Begin()
	{
		uint64_t OldCommandSize = this->_Data.Models.size();

		this->_Data = Data();
		this->_Data.Models.reserve(OldCommandSize);
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
			for (const auto& Model : this->_Data.Models)
			{
				if (!Model.Discriminated)
				{
					if (Model.material != PrevMaterial)
					{
						Model.material->UpdateShader();
						PrevMaterial = Model.material;
					}

					Ref<Shader> MaterialShader = Model.material->GetShader();

					if (MaterialShader->HasUniform(VOLUND_UNIFORM_NAME_MODELMATRIX))
					{
						MaterialShader->SetMat4x4(VOLUND_UNIFORM_NAME_MODELMATRIX, Model.ModelMatrix);
					}

					Model.mesh->Bind();
					this->_API->DrawIndexed(Model.mesh);
				}
			}

			Eye.Target->Unbind();
		}
	}
}
