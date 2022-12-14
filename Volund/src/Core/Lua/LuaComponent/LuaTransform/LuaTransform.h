#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"
#include "Core/Lua/LuaVec/LuaVec.h"

#include "Core/Scene/Component/Transform/Transform.h"

namespace Volund
{
	struct LuaTransform
	{
	public:

		void SetPosition(const LuaVec3& Position);
		LuaVec3 GetPosition() const;
		void AddPosition(const LuaVec3& Position);

		void SetRotation(const LuaVec3& Rotation);
		LuaVec3 GetRotation() const;
		void AddRotation(const LuaVec3& Rotation);

		void SetScale(const LuaVec3& Scale);
		LuaVec3 GetScale() const;
		void AddScale(const LuaVec3& Scale);

		LuaVec3 GetFront() const;
		LuaVec3 GetRight() const;
		LuaVec3 GetUp() const;

		LuaTransform(Ref<Transform> Transform);

	private:

		Ref<Transform> _Transform;
	};
}