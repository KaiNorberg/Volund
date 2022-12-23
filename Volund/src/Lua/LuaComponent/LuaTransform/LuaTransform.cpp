#include "PCH/PCH.h"
#include "LuaTransform.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"

namespace Volund
{
	void LuaTransform::SetPosition(const LuaVec3& Position)
	{
		this->_Transform->Position = Position;
	}

	LuaVec3 LuaTransform::GetPosition() const
	{
		return this->_Transform->Position;
	}

	void LuaTransform::AddPosition(const LuaVec3& Position)
	{
		this->_Transform->Position += (glm::vec3)Position;
	}

	void LuaTransform::SetRotation(const LuaVec3& Rotation)
	{
		this->_Transform->SetRotation(Rotation);
	}

	LuaVec3 LuaTransform::GetRotation() const
	{
		return this->_Transform->GetRotation();
	}

	void LuaTransform::AddRotation(const LuaVec3& Rotation)
	{
		this->_Transform->AddRotation(Rotation);
	}

	void LuaTransform::SetScale(const LuaVec3& Scale)
	{
		this->_Transform->Scale = Scale;
	}

	LuaVec3 LuaTransform::GetScale() const
	{
		return this->_Transform->Scale;
	}

	void LuaTransform::AddScale(const LuaVec3& Scale)
	{
		this->_Transform->Scale += (glm::vec3)Scale;
	}

	LuaVec3 LuaTransform::GetFront() const
	{
		return this->_Transform->GetFront();
	}

	LuaVec3 LuaTransform::GetRight() const
	{
		return this->_Transform->GetRight();
	}

	LuaVec3 LuaTransform::GetUp() const
	{
		return this->_Transform->GetUp();
	}

	LuaTransform::LuaTransform(Ref<Transform> Transform)
	{
		this->_Transform = Transform;
	}
}