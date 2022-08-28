#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	Ref<Context> Renderer::_Context;
	Ref<RenderingAPI> Renderer::_RenderingAPI;

	void Renderer::SubmitScene(Ref<Scene> const& scene)
	{
		//TODO
	}

	void Renderer::BeginScene()
	{
		_RenderingAPI->Clear();
	}

	void Renderer::EndScene()
	{
		_Context->Flush();
	}

	void Renderer::Submit(Ref<VertexArray> const& VArray)
	{
		_RenderingAPI->DrawIndexed(VArray);
	}
	
	void Renderer::Init(Ref<Window>& window)
	{
		_RenderingAPI.reset(RenderingAPI::Create());
		_Context.reset(Context::Create(window));
	
		_RenderingAPI->SetClearColor(RGBA(0.7f, 0.0f, 0.4f, 1.0f));
	}
}