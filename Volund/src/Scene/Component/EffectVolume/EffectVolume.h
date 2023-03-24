#pragma once

#include "Scene/Component/Component.h"
#include "Renderer/Shader/Shader.h"

namespace Volund
{
	class EffectVolume : public Component
	{
	public:

		void Procedure(const Event& E);

	private:

		std::vector<Shader> _PostEffects;
		std::vector<Shader> _PreEffects;

	};
}
