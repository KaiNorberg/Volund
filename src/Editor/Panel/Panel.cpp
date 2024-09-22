#include "Panel.h"

#include <imgui.h>

bool Panel::IsWindowHovered()
{
	return this->m_IsWindowHovered;
}

void Panel::SetName(std::string const& name)
{
	this->m_Name = name;
}

std::string Panel::GetName()
{
	return this->m_Name;
}

std::string Panel::GetId()
{
	return this->m_Name + "##" + this->m_Id;
}

void Panel::Procedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		if (ImGui::Begin(this->GetId().c_str(), &this->m_IsActive))
		{
			this->OnProcedure(e);

			this->m_IsWindowHovered = ImGui::IsWindowHovered();
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
