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
			return a.material < b.material;
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

			Volund::RenderingAPI::Clear();
			Volund::RenderingAPI::SetViewPort(0, 0, (int32_t)targetSpec.Width, (int32_t)targetSpec.Height);

			std::shared_ptr<Material> prevMaterial = nullptr;
			for (const auto& model : this->m_Data.Models)
			{
				if (model.material == nullptr)
				{
					continue;
				}

				auto shader = model.material->GetShader();

				if (shader == nullptr || shader->GetId() == 0)
				{
					continue;
				}

				if (model.mesh == nullptr)
				{
					continue;
				}

				const Frustum cameraFrustum(eye.ProjectionMatrix * eye.ViewMatrix);
				const AABB modelAABB = model.mesh->GetAABB(model.ModelMatrix);

				bool isInMask = (model.LayerMask & eye.LayerMask) != 0;

				if (cameraFrustum.ContainsAABB(modelAABB) && isInMask)
				{
					if (model.material != prevMaterial)
					{
						shader->Bind();
						model.material->UpdateShader();

						prevMaterial = model.material;
					}

					if (shader->HasUniform(VOLUND_UNIFORM_NAME_MODELMATRIX))
					{
						shader->SetMat4x4(VOLUND_UNIFORM_NAME_MODELMATRIX, model.ModelMatrix);
					}

					model.mesh->Bind();
					auto indexBuffer = model.mesh->GetIndexBuffer();
					auto vertexBuffer = model.mesh->GetVertexBuffer();

					if (indexBuffer != nullptr)
					{
						Volund::RenderingAPI::DrawIndexed(indexBuffer->GetCount());
					}
					else if (vertexBuffer != nullptr)
					{
						Volund::RenderingAPI::Draw(0, vertexBuffer->GetCount());
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
					Volund::RenderingAPI::Draw(0, 6);
				}
			}

			eye.Target->Unbind();
		}
	}

	std::shared_ptr<ForwardRenderer> ForwardRenderer::Create()
	{
		return std::shared_ptr<ForwardRenderer>(new ForwardRenderer());
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
