#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	Renderer::SceneData Renderer::_SceneData;

	Ref<Context> Renderer::_Context;
	Ref<RenderingAPI> Renderer::_RenderingAPI;

	void Renderer::BeginScene(Camera* Cam)
	{
		_SceneData.ViewProjMatrix = Cam->GetProjectionMatrix() * Cam->GetViewMatrix();
		_RenderingAPI->Clear();
	}

	void Renderer::EndScene()
	{
		_SceneData = SceneData();
		_Context->Flush();
	}

	void Renderer::Submit(Ref<VertexArray> const& VArray, Ref<Shader> const& shader)
	{
		shader->Bind();
		shader->SetMat4x4(_SceneData.ViewProjMatrix, "ViewProjMatrix");
		VArray->Bind();
		_RenderingAPI->DrawIndexed(VArray);
	}

	Renderer::Renderer(Ref<Window>& window)
	{
		_RenderingAPI.reset(RenderingAPI::Create());
		_Context.reset(Context::Create(window));

		_RenderingAPI->SetClearColor(RGBA(0.7f, 0.0f, 0.4f, 1.0f));
	}

	Renderer::~Renderer()
	{
		_RenderingAPI.reset();
		_Context.reset();
	}
}