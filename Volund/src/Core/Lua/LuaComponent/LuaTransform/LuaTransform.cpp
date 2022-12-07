#include "PCH/PCH.h"
#include "LuaTransform.h"

#include "Core/Scene/Component/Components.h"

#include "Core/Lua/LuaMaterial/LuaMaterial.h"
#include "Core/Lua/LuaMesh/LuaMesh.h"

namespace Volund
{
	void LuaTransform::SetPosition(const Vec3& Position)
	{
		this->_Transform->Position = Position;
	}

	Vec3 LuaTransform::GetPosition() const
	{
		return this->_Transform->Position;
	}

	void LuaTransform::AddPosition(const Vec3& Position)
	{
		this->_Transform->Position += Position;
	}

	void LuaTransform::SetRotation(const Vec3& Rotation)
	{
		this->_Transform->SetRotation(Rotation);
	}

	Vec3 LuaTransform::GetRotation() const
	{
		return this->_Transform->GetRotation();
	}

	void LuaTransform::AddRotation(const Vec3& Rotation)
	{
		this->_Transform->AddRotation(Rotation);
	}

	void LuaTransform::SetScale(const Vec3& Scale)
	{
		this->_Transform->Scale = Scale;
	}

	Vec3 LuaTransform::GetScale() const
	{
		return this->_Transform->Scale;
	}

	void LuaTransform::AddScale(const Vec3& Scale)
	{
		this->_Transform->Scale += Scale;
	}

	Vec3 LuaTransform::GetFront() const
	{
		return this->_Transform->GetFront();
	}

	Vec3 LuaTransform::GetRight() const
	{
		return this->_Transform->GetRight();
	}

	Vec3 LuaTransform::GetUp() const
	{
		return this->_Transform->GetUp();
	}

	LuaTransform::LuaTransform(Ref<Transform> Transform)
	{
		this->_Transform = Transform;
	}
}