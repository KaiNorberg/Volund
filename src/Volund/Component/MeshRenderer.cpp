#include "Component/MeshRenderer.hpp"

#include "Scene.hpp"
#include "Component/Transform.hpp"
#include "Lua/LuaAPI.hpp"
#include "Rendering/Renderer.hpp"

namespace Volund
{
	bool MeshRenderer::IsValid()
	{
		return this->m_mesh != nullptr && this->m_material != nullptr;
	}

	void MeshRenderer::SetLayer(const uint8_t layer)
	{
		this->m_layerMask = 0;
		if (layer > 0 && layer <= 32)
		{
			this->m_layerMask |= 1UL << (layer - 1);
		}
	}

	uint32_t MeshRenderer::GetLayerMask()
	{
		return this->m_layerMask;
	}

	void MeshRenderer::SetMesh(const std::shared_ptr<Mesh> newMesh)
	{
		this->m_mesh = newMesh;
	}

	void MeshRenderer::SetMaterial(const std::shared_ptr<Material> newMaterial)
	{
		this->m_material = newMaterial;
	}

	std::shared_ptr<Mesh> MeshRenderer::GetMesh()
	{
		return this->m_mesh;
	}

	std::shared_ptr<Material> MeshRenderer::GetMaterial()
	{
		return this->m_material;
	}

	void MeshRenderer::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	{
		this->m_mesh = mesh;
		this->m_material = material;
	}

    VOLUND_USERTYPE_COMPONENT_REGISTER(MeshRenderer,
    [](LuaState* state){
        state->NewUsertype<MeshRenderer>("MeshRenderer", 
            sol::constructors<>(),
            "is_valid", &MeshRenderer::IsValid,
            "set_layer", &MeshRenderer::SetLayer,
            "get_layer_mask", &MeshRenderer::GetLayerMask,
            "set_mesh", &MeshRenderer::SetMesh,
            "set_material", &MeshRenderer::SetMaterial,
            "get_mesh", &MeshRenderer::GetMesh,
            "get_material", &MeshRenderer::GetMaterial
        );
    }, std::shared_ptr<Mesh>, std::shared_ptr<Material>);
}