#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	void Renderer::Init(const Ref<RendererInstance>& Instance)
	{
		_Instance = Instance;
	}

	void Renderer::Init(RendererInstance* Instance)
	{
		_Instance = Ref<RendererInstance>(Instance);
	}

	void Renderer::Reset()
	{
		_Instance.reset();
	}

	void Renderer::Begin(const Mat4x4& ViewMatrix, const Mat4x4& ProjectionMatrix)
	{
		_Instance->Begin(ViewMatrix, ProjectionMatrix);
	}

	void Renderer::Submit(const RendererCommand& Command)
	{
		_Instance->Submit(Command);
	}

	void Renderer::Submit(const RendererLight& Light)
	{
		_Instance->Submit(Light);
	}

	void Renderer::End()
	{
		_Instance->End();
	}
}
