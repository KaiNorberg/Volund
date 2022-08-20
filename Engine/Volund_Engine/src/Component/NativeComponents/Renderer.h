#pragma once

#include "Component/NativeComponent.h"

#define RENDERER_COMPONENT "Renderer"

namespace Volund
{
	class Entity;

	class Renderer : public NativeComponent
	{
	public:

		const std::string Type() override;

		Renderer() = default;

		Renderer(Entity* Parent, JSON ComponentJSON);

	private:

	};
}
