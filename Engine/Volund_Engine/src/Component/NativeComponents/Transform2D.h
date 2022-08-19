#pragma once

#include "Component/NativeComponent.h"

#include "Math/Vec/Vec2.h"

namespace Volund
{
	class Entity;

	class Transform2D : public NativeComponent
	{
	public:

		Vec2 Position;

		Vec2 Scale;

		const std::string Name() override;

		Transform2D() = default;

		Transform2D(Entity* Parent, JSON ComponentJSON);

	private:

		Entity* Parent;
	};
}

