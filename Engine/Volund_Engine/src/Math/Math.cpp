#include "PCH/PCH.h"

#include "Math.h"

namespace Volund::Math
{
	Vec3 Euler(Quat const& Q)
	{
		return ToDegrees(glm::eulerAngles(Q));
	}
}