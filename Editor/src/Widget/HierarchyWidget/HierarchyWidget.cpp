#include "PCH/PCH.h"
#include "HierarchyWidget.h"

#include "Editor/EditorModule/EditorModule.h"

const char* HierarchyWidget::GetName()
{
	return "Hierarchy";
}

void HierarchyWidget::OnRender()
{
	auto scene = this->m_App->GetModule<VL::GameModule>()->GetScene();

	if (ImGui::Begin("Entities", &this->IsActive))
	{
		if (scene != nullptr)
		{
			if (ImGui::Button("+"))
			{
				scene->RegisterNewEntity();
			}
			ImGui::SameLine();

			static char searchTerm[64];
			ImGui::Text("Search: ");
			ImGui::SameLine();
			ImGui::InputText(" ", searchTerm, 64);

			if (scene != nullptr)
			{
				for (auto& [entity, container] : *scene)
				{
					std::string entityName = "#" + std::to_string(entity);
					if (scene->HasComponent<VL::Tag>(entity))
					{
						entityName += " | " + scene->GetComponent<VL::Tag>(entity)->String;
					}

					if (entityName.find(searchTerm) != std::string::npos)
					{
						if (!this->DrawEntityNode(entity, entityName))
						{
							break;
						}
					}
				}
			}
		}
		else
		{
			ImGui::Text("No Scene Selected!");
		}

	}

	ImGui::End();
}

bool HierarchyWidget::DrawEntityNode(VL::Entity entity, const std::string& entityName)
{
	auto scene = this->m_App->GetModule<VL::GameModule>()->GetScene();

	auto& selectedEntity = this->m_App->GetModule<EditorModule>()->SelectedEntity;

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

HierarchyWidget::HierarchyWidget(VL::Application* app)
{
	this->m_App = app;
}