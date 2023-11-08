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

		LightsBuffer lightsBuffer;
		lightsBuffer.LightAmount = std::min((uint32_t)this->m_Data.Lights.size(), (uint32_t)VOLUND_FORWARD_RENDERER_MAX_LIGHTS);
		for (uint64_t i = 0; i < lightsBuffer.LightAmount; i++)
		{
			Vec3 lightColor = this->m_Data.Lights[i].Color * this->m_Data.Lights[i].Brightness;
			Vec3 lightPosition = this->m_Data.Lights[i].Position;

			lightsBuffer.LightColors[i] = Vec4(lightColor.x, lightColor.y, lightColor.z, 0.0f);
			lightsBuffer.LightPositions[i] = Vec4(lightPosition.x, lightPosition.y, lightPosition.z, 0.0f);
		}
		this->m_LightsUniformBuffer->SetData(&lightsBuffer, sizeof(LightsBuffer), 0);

		for (const auto& eye : this->m_Data.Eyes)
		{
			CameraBuffer cameraBuffer;
			cameraBuffer.ProjectionMatrix = eye.ProjectionMatrix;
			cameraBuffer.ViewMatrix = eye.ViewMatrix;
			this->m_CameraUniformBuffer->SetData(&cameraBuffer, sizeof(CameraBuffer), 0);

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

				const Frustum cameraFrustum(eye.ProjectionMatrix * eye.ViewMatrix);

				bool isInFrustum = model.ModelMesh != nullptr && cameraFrustum.ContainsAABB(model.ModelMesh->GetAABB(model.ModelMatrix));
				bool isInMask = (model.LayerMask & eye.LayerMask) != 0;

				if (isInFrustum && isInMask)
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

	ForwardRenderer::ForwardRenderer()
	{
		this->m_CameraUniformBuffer = UniformBuffer::Create(sizeof(CameraBuffer), VOLUND_FORWARD_RENDERER_BINDING_CAMERA);
		this->m_LightsUniformBuffer = UniformBuffer::Create(sizeof(LightsBuffer), VOLUND_FORWARD_RENDERER_BINDING_LIGHTS);
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
