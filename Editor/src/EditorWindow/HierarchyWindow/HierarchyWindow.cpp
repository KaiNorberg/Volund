#include "PCH/PCH.h"
#include "HierarchyWindow.h"

void HierarchyWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		auto scene = this->m_Context->GetScene();

		if (scene != nullptr)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
			ImGui::Separator();

			if (ImGui::Button("+"))
			{
				scene->RegisterNewEntity();
			}

			ImGui::SameLine();
			static char searchTerm[64];
			ImGui::Text("Search: ");
			ImGui::SameLine();
			ImGui::InputText(" ", searchTerm, 64);

			for (auto& [entity, container] : *scene)
			{
				std::string entityName = "#" + std::to_string(entity);
				if (scene->HasComponent<VL::Tag>(entity))
				{
					entityName += " | " + scene->GetComponent<VL::Tag>(entity)->String;
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
		else
		{
			ImGui::Text("No Scene Loaded!");
		}
	}
	break;
	}
}

bool HierarchyWindow::ImGuiEntity(VL::Entity entity, const std::string& entityName)
{
	auto scene = this->m_Context->GetScene();
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
			scene->UnregisterEntity(entity);
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