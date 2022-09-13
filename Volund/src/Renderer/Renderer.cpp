#include "PCH/PCH.h"
#include "Renderer.h"

#include "Scene/Entity/Component/Transform/Transform.h"
#include "Scene/Entity/Component/PointLight/PointLight.h"

namespace Volund
{
	void Renderer::BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, const std::vector<PointLightData>& PointLights)
	{
		_SceneData = SceneData();
		_SceneData.ViewProjMatrix = ViewProjMatrix;
		_SceneData.EyePosition = EyePosition;
		_SceneData.PointLights = PointLights;

		InScene = true;
	}

	void Renderer::BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, const std::vector<Ref<PointLight>>& PointLights)
	{
		_SceneData = SceneData();
		_SceneData.ViewProjMatrix = ViewProjMatrix;
		_SceneData.EyePosition = EyePosition;

		_SceneData.PointLights.reserve(PointLights.size());
		for (auto const& Light : PointLights)
		{
			_SceneData.PointLights.push_back({ Light->Color, Light->GetEntity()->GetComponent<Transform>()->Position });
		}

		InScene = true;
	}

	void Renderer::EndScene(const Ref<Context>& RenderingContext)
	{
		RenderingContext->MakeCurrent();

		_API->SetClearColor(RGBA(0.0f, 0.0f, 0.0f, 1.0f));

		_API->Clear();

		_API->SetViewPort(0, 0, (int32_t)RenderingContext->GetWindow()->GetSize().x,
		                  (int32_t)RenderingContext->GetWindow()->GetSize().y);

		for (Submission Data : _SceneData.Submissions)
		{
			Data.ObjectMaterial->UpdateShader();
			Ref<Shader> ObjectShader = Data.ObjectMaterial->GetShader();

			if (ObjectShader->HasUniform("PointLights[0].Color"))
			{
				ObjectShader->SetInt("PointLightAmount", (int32_t)_SceneData.PointLights.size());

				for (uint64_t i = 0; i < _SceneData.PointLights.size(); i++)
				{
					std::string Uniform = "PointLights[" + std::to_string(i) + "].";
					ObjectShader->SetVec3(Uniform + "Color", _SceneData.PointLights[i].Color);
					ObjectShader->SetVec3(Uniform + "Position", _SceneData.PointLights[i].Position);
				}
			}

			ObjectShader->SetMat4x4("ModelMatrix", Data.ModelMatrix);
			ObjectShader->SetMat4x4("ViewProjMatrix", _SceneData.ViewProjMatrix);
			ObjectShader->SetVec3("EyePosition", _SceneData.EyePosition);

			Data.ObjectMesh->Bind();
			_API->DrawIndexed(Data.ObjectMesh);
		}

		//_SceneData = SceneData();
		RenderingContext->Flush();

		InScene = false;
	}

	void Renderer::Submit(Mat4x4& ModelMatrix, const Ref<Mesh>& ObjectMesh, const Ref<Material>& ObjectMaterial)
	{
		VOLUND_ASSERT(InScene, "Attempting to push a Submission to the Renderer while outside of a Renderer Scene!");

		Submission NewSubmission = Submission();
		NewSubmission.ModelMatrix = ModelMatrix;
		NewSubmission.ObjectMesh = ObjectMesh;
		NewSubmission.ObjectMaterial = ObjectMaterial;

		_SceneData.Submissions.push_back(NewSubmission);
	}

	void Renderer::Init(const Ref<RenderingAPI>& API)
	{
		_API = API;
		_API->Init();
	}
}
