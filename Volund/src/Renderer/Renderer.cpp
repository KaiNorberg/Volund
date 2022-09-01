#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	Renderer::SceneData Renderer::_SceneData;

	Ref<Context> Renderer::_Context;
	Ref<RenderingAPI> Renderer::_RenderingAPI;

	void Renderer::BeginScene(Mat4x4& ViewProjMatrix)
	{
		SceneData NewSceneData = SceneData();
		_SceneData.ViewProjMatrix = ViewProjMatrix;

		_RenderingAPI->Clear();
	}

	void Renderer::EndScene()
	{
		for (EntityData Data : _SceneData.Submissions)
		{
			Data.ObjectShader->Bind();
			Data.ObjectShader->SetMat4x4(_SceneData.ViewProjMatrix, "ViewProjMatrix");
			Data.ObjectShader->SetMat4x4(Data.ModelMatrix, "ModelMatrix");

			Data.ObjectMesh->Bind();
			_RenderingAPI->DrawIndexed(Data.ObjectMesh);
		}

		_SceneData = SceneData();
		_Context->Flush();
	}

	void Renderer::Submit(Mat4x4 ModelMatrix, Ref<Mesh> const& ObjectMesh, Ref<Shader> const& ObjectShader)
	{
		EntityData NewEnityData = EntityData();
		NewEnityData.ModelMatrix = ModelMatrix;
		NewEnityData.ObjectMesh = ObjectMesh;
		NewEnityData.ObjectShader = ObjectShader;

		_SceneData.Submissions.push_back(NewEnityData);
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