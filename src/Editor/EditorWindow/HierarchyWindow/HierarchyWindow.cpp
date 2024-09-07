#include "HierarchyWindow.h"

#include <imgui.h>

void HierarchyWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		auto gameState = this->m_Context->GameState;

		if (ImGui::Button("+"))
		{
			gameState->AllocateEntity();
		}

		ImGui::SameLine();
		static char searchTerm[64];
		ImGui::Text("Search: ");
		ImGui::SameLine();
		ImGui::InputText(" ", searchTerm, 64);

		for (auto& [entity, container] : *gameState)
		{
			std::string entityName;
			if (gameState->HasComponent<VL::Tag>(entity))
			{
				entityName = gameState->GetComponent<VL::Tag>(entity)->String;
			}
			else
			{
				entityName = "Unnamed entity";
			}

			if (entityName.find(searchTerm) != std::string::npos)
			{
				if (!this->ImGuiEntity(entity, entityName))
				{
					break;
				}
			}
		}
	}
	break;
	}
}

bool HierarchyWindow::ImGuiEntity(VL::Entity entity, const std::string& entityName)
{
	auto gameState = this->m_Context->GameState;
	auto& selectedEntity = this->m_Context->SelectedEntity;

	ImGui::PushID((void*)entity);

	bool Open = false;

	ImGuiTreeNodeFlags Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (entity == selectedEntity)
	{
		Flags = Flags | ImGuiTreeNodeFlags_Selected;
	}

	Open = ImGui::TreeNodeEx((void*)entity, Flags, entityName.c_str());


	if (ImGui::IsItemClicked())
	{
		selectedEntity = entity;
	}

	if (Open)
	{
		ImGui::TreePop();
	}

	bool EntityAlive = true;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete"))
		{
			gameState->DeallocateEntity(entity);
			EntityAlive = false;
		}

		ImGui::EndPopup();
	}

	ImGui::PopID();

	return EntityAlive;
}

HierarchyWindow::HierarchyWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Hierarchy");

	this->m_Context = context;
}
