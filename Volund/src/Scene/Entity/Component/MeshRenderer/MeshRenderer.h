#pragma once

#include "../Component.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void OnUpdate(TimeStep TS) override;

		VML Serialize() override;

		void SetMesh(Ref<Mesh> _NewMesh);

		void SetMaterial(Ref<Material> _NewMaterial);

		const Ref<Mesh>& GetMesh();

		const Ref<Material>& GetMaterial();

		MeshRenderer(std::string_view MeshFilePath, std::string_view MaterialFilePath);

	private:
		Ref<Mesh> _Mesh;
		Ref<Material> _Material;
	};
}
