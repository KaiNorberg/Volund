#pragma once

#include "Component/Component.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Shader/Shader.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void OnUpdate(TimeStep TS) override;

		MeshRenderer(Ref<Mesh> DrawMesh, Ref<Shader> DrawShader);

	private:

		Ref<Mesh> _Mesh;
		Ref<Shader> _Shader;
	};
}