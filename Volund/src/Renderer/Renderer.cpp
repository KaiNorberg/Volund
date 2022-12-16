#include "PCH/PCH.h"
#include "Renderer.h"

#include "Frustum/Frustum.h"

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

	void Renderer::Begin()
	{
		_Instance->Begin();
	}

	void Renderer::Submit(const RendererCommand& Command)
	{
		_Instance->Submit(Command);
	}

	void Renderer::Submit(const RendererLight& Light)
	{
		_Instance->Submit(Light);
	}

	void Renderer::Submit(const RendererEye& Eye)
	{
		_Instance->Submit(Eye);
	}

	void Renderer::End()
	{
		_Instance->End();
	}

	void RendererInstance::Data::Sort()
	{
		std::sort(this->CommandQueue.begin(), this->CommandQueue.end(), [](const RendererCommand& A, const RendererCommand& B)
		{
			return A.material < B.material;
		});
	}

	void RendererInstance::Data::Discriminate(const RendererEye& Eye)
	{
		Frustum CameraFrustum(Eye.ProjectionMatrix * Eye.ViewMatrix);

		for (auto& Command : this->CommandQueue)
		{
			Command.Discriminated = !CameraFrustum.ContainsAABB(Command.mesh->GetAABB(Command.ModelMatrix));
		}
	}
}
