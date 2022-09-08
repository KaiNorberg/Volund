#pragma once

#include "Renderer/Shader/Shader.h"

namespace Volund
{
	class Material
	{
	public:
		Ref<Shader> GetShader();

		static Ref<Material> Create(Ref<Shader> ObjectShader);

		Material(Ref<Shader> ObjectShader);

	private:
		Ref<Shader> _Shader;
	};
}
