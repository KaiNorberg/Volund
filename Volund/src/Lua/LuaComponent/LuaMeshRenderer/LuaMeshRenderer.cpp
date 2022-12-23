#include "PCH/PCH.h"
#include "LuaMeshRenderer.h"

namespace Volund
{
	void LuaMeshRenderer::SetMesh(LuaMesh NewMesh)
	{
		this->_MeshRenderer->SetMesh(NewMesh.Get());
	}

	void LuaMeshRenderer::SetMaterial(LuaMaterial NewMaterial)
	{
		this->_MeshRenderer->SetMaterial(NewMaterial.Get());
	}

	LuaMesh LuaMeshRenderer::GetMesh()
	{
		return LuaMesh(this->_MeshRenderer->GetMesh());
	}

	LuaMaterial LuaMeshRenderer::GetMaterial()
	{
		return LuaMaterial(this->_MeshRenderer->GetMaterial());
	}

	LuaMeshRenderer::LuaMeshRenderer(Ref<MeshRenderer> MeshRenderer)
	{
		this->_MeshRenderer = MeshRenderer;
	}
}