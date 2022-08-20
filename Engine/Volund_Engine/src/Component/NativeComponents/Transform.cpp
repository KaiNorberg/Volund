#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	const std::string Transform::Name()
	{
		return TRANSFORM_COMPONENT;
	}

	Transform::Transform(Entity* Parent, JSON ComponentJSON)
	{
		this->Parent = Parent;

		/*if (ComponentJSON.contains("Position"))
		{
			JSON JSONPosition = ComponentJSON["Position"];
			if (JSONPosition.is_array() && JSONPosition.size() == 3)
			{
				this->Position.X = JSONPosition[0];
				this->Position.Y = JSONPosition[1];				
				this->Position.Z = JSONPosition[2];
			}
		}
		if (ComponentJSON.contains("Scale"))
		{
			JSON JSONScale = ComponentJSON["Scale"];
			if (JSONScale.is_array() && JSONScale.size() == 3)
			{
				this->Scale.X = JSONScale[0];
				this->Scale.Y = JSONScale[1];				
				this->Scale.Z = JSONScale[2];
			}
		}*/
	}
}

