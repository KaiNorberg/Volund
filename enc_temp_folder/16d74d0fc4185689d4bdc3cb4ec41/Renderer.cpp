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

	void RendererInstance::Data::Sort()
	{
		std::sort(this->CommandQueue.begin(), this->CommandQueue.end(), [](const RendererCommand& A, const RendererCommand& B)
		{
			return A.material < B.material;
		});
	}

	void RendererInstance::Data::Discriminate()
	{
		Frustum CameraFrustum(this->ProjectionMatrix * this->ViewMatrix);

		for (int i = 0; i < this->CommandQueue.size(); i++)
		{
			if (!CameraFrustum.ContainsAABB(this->CommandQueue[i].mesh->GetAABB(this->CommandQueue[i].ModelMatrix)))
			{
				this->CommandQueue.erase(this->CommandQueue.begin() + i);
			}
		}
	}
}
