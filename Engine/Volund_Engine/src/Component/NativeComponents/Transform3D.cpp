#include "PCH/PCH.h"

#include "Transform3D.h"

namespace Volund
{
	const std::string Transform3D::Name()
	{
		return "Transform3D";
	}

	Transform3D::Transform3D(Entity* Parent, JSON ComponentJSON)
	{
		this->Parent = Parent;
	}
}

