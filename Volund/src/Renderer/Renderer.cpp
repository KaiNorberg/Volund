#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	void Renderer::BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, std::vector<PointLightData> const& PointLights)
	{
		SceneData NewSceneData = SceneData();
		_SceneData.ViewProjMatrix = ViewProjMatrix;
		_SceneData.EyePosition = EyePosition;
		_SceneData.PointLights = PointLights;
	
		InScene = true;
	}

	void Renderer::EndScene()
	{
		_RenderingAPI->Clear();

		_RenderingAPI->SetViewPort(0, 0,(uint32_t)_Window->GetSize().x, (uint32_t)_Window->GetSize().y);

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

		InScene = false;
	}

	void Renderer::Submit(Mat4x4& ModelMatrix, Ref<Mesh> const& ObjectMesh, Ref<Material> const& ObjectMaterial)
	{
		VOLUND_ASSERT(InScene, "Attempting to push a Submission to the Renderer while outside of a Renderer Scene!");

		Submission NewSubmission = Submission();
		NewSubmission.ModelMatrix = ModelMatrix;
		NewSubmission.ObjectMesh = ObjectMesh;
		NewSubmission.ObjectMaterial = ObjectMaterial;

		_SceneData.Submissions.push_back(NewSubmission);
	}

	Ref<Context> Renderer::GetContext()
	{
		return _Context;
	}

	Ref<Window> Renderer::GetWindow()
	{
		return _Window;
	}

	void Renderer::SetWindow(Ref<Window> const& NewWindow)
	{
		if (NewWindow != nullptr)
		{
			_RenderingAPI = RenderingAPI::Create();
			_Context = Context::Create(NewWindow);

			_RenderingAPI->SetClearColor(RGBA(0.0f, 0.0f, 0.0f, 1.0f));

			_SceneData.Submissions.reserve(32);
		}
		else
		{
			_RenderingAPI.reset();
			_Context.reset();
		}
		
		_Window = NewWindow;
	}
}