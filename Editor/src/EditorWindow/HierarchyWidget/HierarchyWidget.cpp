#include "PCH/PCH.h"
#include "HierarchyWidget.h"

#include "Editor/EditorContext/EditorContext.h"

const char* HierarchyWidget::GetName()
{
	return "Hierarchy";
}

void HierarchyWidget::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		if (ImGui::Begin(this->GetName(), &this->IsActive))
		{
			auto scene = this->m_Context->GetScene();

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
	break;
	case VL::EventType::Update:
	{
	}
	break;
	}
}

bool HierarchyWidget::DrawEntityNode(VL::Entity entity, const std::string& entityName)
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

HierarchyWidget::HierarchyWidget(VL::Ref<EditorContext> context)
{
	this->m_Context = context;
}