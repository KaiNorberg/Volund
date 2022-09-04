#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	Renderer::SceneData Renderer::_SceneData;

	Ref<Context> Renderer::_Context;
	Ref<RenderingAPI> Renderer::_RenderingAPI;

	void Renderer::BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, std::vector<PointLightData> const& PointLights)
	{
		SceneData NewSceneData = SceneData();
		_SceneData.ViewProjMatrix = ViewProjMatrix;
		_SceneData.EyePosition = EyePosition;
		_SceneData.PointLights = PointLights;

		_RenderingAPI->Clear();
	}

	void Renderer::EndScene()
	{
		for (Submission Data : _SceneData.Submissions)
		{
			Ref<Shader> ObjectShader = Data.ObjectMaterial->GetShader();
			ObjectShader->Bind();

			ObjectShader->SetMat4x4("ViewProjMatrix", _SceneData.ViewProjMatrix);
			ObjectShader->SetVec3("EyePosition", _SceneData.EyePosition);
			if (ObjectShader->HasUniform("PointLights[0].Color"))
			{
				ObjectShader->SetInt("PointLightAmount", (uint32_t)_SceneData.PointLights.size());

				for (int i = 0; i < _SceneData.PointLights.size(); i++)
				{
					std::string Uniform = "PointLights[" + std::to_string(i) + "].";
					ObjectShader->SetVec3(Uniform + "Color", _SceneData.PointLights[i].Color);
					ObjectShader->SetVec3(Uniform + "Position", _SceneData.PointLights[i].Position);
				}
			}

			ObjectShader->SetMat4x4("ModelMatrix", Data.ModelMatrix);

			Data.ObjectMesh->Bind();
			_RenderingAPI->DrawIndexed(Data.ObjectMesh);
		}

		_SceneData = SceneData();
		_Context->Flush();
	}

	void Renderer::Submit(Mat4x4& ModelMatrix, Ref<Mesh> const& ObjectMesh, Ref<Material> const& ObjectMaterial)
	{
		Submission NewSubmission = Submission();
		NewSubmission.ModelMatrix = ModelMatrix;
		NewSubmission.ObjectMesh = ObjectMesh;
		NewSubmission.ObjectMaterial = ObjectMaterial;

		_SceneData.Submissions.push_back(NewSubmission);
	}

	Renderer::Renderer(Ref<Window>& window)
	{
		_RenderingAPI = RenderingAPI::Create();
		_Context = Context::Create(window);

		_RenderingAPI->SetClearColor(RGBA(0.7f, 0.0f, 0.4f, 1.0f));

		_SceneData.Submissions.reserve(32);
	}

	Renderer::~Renderer()
	{
		_RenderingAPI.reset();
		_Context.reset();
	}
}