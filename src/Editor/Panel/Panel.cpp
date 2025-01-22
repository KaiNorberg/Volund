#include "Panel.hpp"

#include <imgui.h>

bool Panel::IsWindowHovered()
{
	return this->m_isWindowHovered;
}

void Panel::SetName(std::string const& name)
{
	this->m_name = name;
}

std::string Panel::GetName()
{
	return this->m_name;
}

std::string Panel::GetId()
{
	return this->m_name + "##" + this->m_id;
}

void Panel::Procedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		if (ImGui::Begin(this->GetId().c_str(), &this->m_isActive))
		{
			this->OnProcedure(e);

			this->m_isWindowHovered = ImGui::IsWindowHovered();
		}

		ImGui::End();
	}
	break;
	default:
	{
		this->OnProcedure(e);
	}
	break;
	}
}
