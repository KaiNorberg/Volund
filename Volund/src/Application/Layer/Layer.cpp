#include "PCH/PCH.h"
#include "Layer.h"

namespace Volund
{
	Application* Layer::GetApp()
	{
		return this->_Parent;

	}
	
	void Layer::SetParent(Application* Parent)
	{
		this->_Parent = Parent;
	}
}