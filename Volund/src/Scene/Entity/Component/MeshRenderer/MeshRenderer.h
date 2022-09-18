#pragma once

#include "../Component.h"

#include "Asset/Asset.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void OnUpdate(TimeStep TS) override;

		VML Serialize() override;

		void SetMesh(Asset<Mesh> _NewMesh);

		void SetMaterial(Asset<Material> _NewMaterial);

		const Asset<Mesh>& GetMesh();

		const Asset<Material>& GetMaterial();

		MeshRenderer(std::string_view MeshFilePath, std::string_view MaterialFilePath);

	private:
		Asset<Mesh> _Mesh;
		Asset<Material> _Material;
	};
}
