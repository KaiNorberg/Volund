#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

#include "Core/Scene/Component/Transform/Transform.h"

namespace Volund
{
	struct LuaTransform
	{
	public:

		void SetPosition(const Vec3& Position);
		Vec3 GetPosition() const;
		void AddPosition(const Vec3& Position);

		void SetRotation(const Vec3& Rotation);
		Vec3 GetRotation() const;
		void AddRotation(const Vec3& Rotation);

		void SetScale(const Vec3& Scale);
		Vec3 GetScale() const;
		void AddScale(const Vec3& Scale);

		Vec3 GetFront() const;
		Vec3 GetRight() const;
		Vec3 GetUp() const;

		LuaTransform(Ref<Transform> Transform);

	private:

		Ref<Transform> _Transform;
	};
}