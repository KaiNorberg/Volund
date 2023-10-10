#include "PCH/PCH.h"
#include "SerialObject.h"

#include "../SerialTable.h"

namespace Volund
{
	void PrimitiveSerialObject::operator=(SerialTable data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(LuaInt data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(LuaFloat data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(LuaBool data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(LuaString data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(Vec2 data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(Vec3 data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
	void PrimitiveSerialObject::operator=(Vec4 data)
	{
		VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
	}
}