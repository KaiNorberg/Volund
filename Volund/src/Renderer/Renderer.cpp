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
			Data.DrawShader->Bind();
			Data.DrawShader->SetMat4x4(_SceneData.ViewProjMatrix, "ViewProjMatrix");
			Data.DrawShader->SetMat4x4(Data.ModelMatrix, "ModelMatrix");

			Data.VArray->Bind();
			_RenderingAPI->DrawIndexed(Data.VArray);
		}

		_SceneData = SceneData();
		_Context->Flush();
	}

	void Renderer::Submit(Mat4x4& ModelMatrix, Ref<VertexArray> const& VArray, Ref<Shader> const& DrawShader)
	{
		EntityData NewEnityData = EntityData();
		NewEnityData.ModelMatrix = ModelMatrix;
		NewEnityData.VArray = VArray;
		NewEnityData.DrawShader = DrawShader;

		_SceneData.Submissions.push_back(NewEnityData);
	}

	Renderer::Renderer(Ref<Window>& window)
	{
		_RenderingAPI.reset(RenderingAPI::Create());
		_Context.reset(Context::Create(window));

		_RenderingAPI->SetClearColor(RGBA(0.7f, 0.0f, 0.4f, 1.0f));

		_SceneData.Submissions.reserve(32);
	}

	Renderer::~Renderer()
	{
		_RenderingAPI.reset();
		_Context.reset();
	}
}