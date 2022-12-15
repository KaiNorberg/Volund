#include "PCH/PCH.h"
#include "AABB.h"

namespace Volund
{
	AABB::AABB(Vec3 Min, Vec3 Max)
	{
		this->Min = Min;
		this->Max = Max;
	}
}