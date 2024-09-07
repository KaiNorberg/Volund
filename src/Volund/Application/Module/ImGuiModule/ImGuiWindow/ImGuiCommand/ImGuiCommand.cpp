#include "PCH/PCH.h"
#include "ImGuiCommand.h"

#include <imgui/imgui.h>

namespace Volund
{
	void ImGuiResizeCommand::Execute(const std::string& id)
	{
		ImGui::SetWindowSize(ImVec2(this->m_NewSize.x, this->m_NewSize.y));
	}

	ImGuiResizeCommand::ImGuiResizeCommand(const Vec2& newSize)
	{
		this->m_NewSize = newSize;
	}

	void ImGuiMoveCommand::Execute(const std::string& id)
	{
		ImGui::SetWindowPos(ImVec2(this->m_NewPosition.x, this->m_NewPosition.y));
	}

	ImGuiMoveCommand::ImGuiMoveCommand(const Vec2& newPosition)
	{
		this->m_NewPosition = newPosition;
	}
}