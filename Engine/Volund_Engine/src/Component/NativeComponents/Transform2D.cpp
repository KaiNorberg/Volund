#include "PCH/PCH.h"

#include "Transform2D.h"

namespace Volund
{
	const std::string Transform2D::Name()
	{
		return "Transform2D";
	}

	Transform2D::Transform2D(Entity* Parent, JSON ComponentJSON)
	{
		this->Parent = Parent;

		if (ComponentJSON.contains("Position") )
		{
			JSON JSONPosition = ComponentJSON["Position"];
			if (JSONPosition.is_array() && JSONPosition.size() == 2)
			{
				this->Position.X = JSONPosition[0];
				this->Position.Y = JSONPosition[1];
			}
		}		
		if (ComponentJSON.contains("Scale"))
		{
			JSON JSONScale = ComponentJSON["Scale"];
			if (JSONScale.is_array() && JSONScale.size() == 2)
			{
				this->Scale.X = JSONScale[0];
				this->Scale.Y = JSONScale[1];
			}
		}
	}
}

