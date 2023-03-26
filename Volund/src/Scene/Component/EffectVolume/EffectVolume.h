#pragma once

#include "Scene/Component/Component.h"
#include "Renderer/Shader/Shader.h"

namespace Volund
{
	class EffectVolume : public Component
	{
	public:

		void Procedure(const Event& e);

	private:

		std::vector<Shader> m_PostEffects;
		std::vector<Shader> m_PreEffects;

	};
}
