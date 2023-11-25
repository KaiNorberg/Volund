#include "PCH/PCH.h"
#include "ForwardRenderer.h"

#include "Frustum/Frustum.h"

namespace Volund
{
	void ForwardRenderer::Begin()
	{
		this->m_Data = Renderer::Data();
	}

	void ForwardRenderer::End()
	{
		std::sort(this->m_Data.Models.begin(), this->m_Data.Models.end(), [](const RendererModel& a, const RendererModel& b)
		{
			return a.Material < b.Material;
		});

		this->m_LightsBuffer->LightAmount = std::min((uint32_t)this->m_Data.Lights.size(), (uint32_t)VOLUND_FORWARD_RENDERER_MAX_LIGHTS);
		for (uint64_t i = 0; i < this->m_LightsBuffer->LightAmount; i++)
		{
			Vec3 lightColor = this->m_Data.Lights[i].Color * this->m_Data.Lights[i].Brightness;
			Vec3 lightPosition = this->m_Data.Lights[i].Position;

			this->m_LightsBuffer->LightColors[i] = Vec4(lightColor.x, lightColor.y, lightColor.z, 0.0f);
			this->m_LightsBuffer->LightPositions[i] = Vec4(lightPosition.x, lightPosition.y, lightPosition.z, 0.0f);
		}
		this->m_LightsBuffer.Update();

		for (const auto& eye : this->m_Data.Eyes)
		{
			this->m_CameraBuffer->ProjectionMatrix = eye.ProjectionMatrix;
			this->m_CameraBuffer->ViewMatrix = eye.ViewMatrix;
			this->m_CameraBuffer.Update();

			eye.Target->Bind();
			auto& targetSpec = eye.Target->GetSpec();

			VL::RenderingAPI::Clear();						
			VL::RenderingAPI::SetViewPort(0, 0, (int32_t)targetSpec.Width, (int32_t)targetSpec.Height);

			Ref<Material> prevMaterial = nullptr;
			for (const auto& model : this->m_Data.Models)
			{
				if (model.Material == nullptr)
				{
					continue;
				}

				auto shader = model.Material->GetShader();

				if (shader == nullptr || shader->GetId() == 0)
				{
					continue;
				}

				if (model.ModelMesh == nullptr)
				{
					continue;
				}

				const Frustum cameraFrustum(eye.ProjectionMatrix * eye.ViewMatrix);
				const AABB modelAABB = model.ModelMesh->GetAABB(model.ModelMatrix);

				bool isInMask = (model.LayerMask & eye.LayerMask) != 0;

				if (cameraFrustum.ContainsAABB(modelAABB) && isInMask)
				{
					if (model.Material != prevMaterial)
					{
						shader->Bind();
						model.Material->UpdateShader();

						prevMaterial = model.Material;
					}

					if (shader->HasUniform(VOLUND_UNIFORM_NAME_MODELMATRIX))
					{
						shader->SetMat4x4(VOLUND_UNIFORM_NAME_MODELMATRIX, model.ModelMatrix);
					}

					model.ModelMesh->Bind();		
					auto indexBuffer = model.ModelMesh->GetIndexBuffer();
					auto vertexBuffer = model.ModelMesh->GetVertexBuffer();
					
					if (indexBuffer != nullptr)
					{
						VL::RenderingAPI::DrawIndexed(indexBuffer->GetCount());
					}
					else if (vertexBuffer != nullptr)
					{
						VL::RenderingAPI::Draw(0, vertexBuffer->GetCount());
					}
					else
					{
						//Not loaded
					}
				}

			}

			for (auto& effect : eye.Effects)
			{
				auto shader = effect->GetShader();

				if (shader != nullptr && shader->GetId() != 0)
				{
					shader->Bind();
					effect->UpdateShader();
					VL::RenderingAPI::Draw(0, 6);
				}
			}

			eye.Target->Unbind();
		}
	}

	Ref<ForwardRenderer> ForwardRenderer::Create()
	{
		return Ref<ForwardRenderer>(new ForwardRenderer());
	}

	/*void Renderer::Data::Sort()
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
			bool isInFrustum = model.ModelMesh != nullptr && cameraFrustum.ContainsAABB(model.ModelMesh->GetAABB(model.ModelMatrix));
			bool isInMask = (model.LayerMask & eye.LayerMask) != 0;

			model.Discriminated = !isInFrustum || !isInMask;
		}
	}*/
}
