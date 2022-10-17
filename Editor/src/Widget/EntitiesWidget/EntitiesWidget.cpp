#include "PCH/PCH.h"
#include "EntitiesWidget.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

const char* EntitiesWidget::GetName()
{
	return "Entities";
}

void EntitiesWidget::Draw(VL::TimeStep TS)
{
	auto Scene = this->_Editor->GetSelectedScene();

	if (ImGui::Begin("Entities", &this->_IsActive))
	{
		if (Scene != nullptr)
		{
			if (ImGui::Button("+"))
			{
				Scene->CreateEntity();
			}
			ImGui::SameLine();

			static char SearchTerm[64];
			ImGui::Text("Search: ");
			ImGui::SameLine();
			ImGui::InputText(" ", SearchTerm, 64);

			if (Scene != nullptr)
			{
				for (auto& [Entity, Container] : *Scene)
				{
					std::string EntityName = "#" + std::to_string(Entity);
					if (Scene->HasComponent<VL::Tag>(Entity))
					{
						EntityName += " | " + Scene->GetComponent<VL::Tag>(Entity)->String;
					}

					if (EntityName.find(SearchTerm) != std::string::npos)
					{
						if (!this->DrawEntityNode(Scene, Entity, EntityName))
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

bool EntitiesWidget::DrawEntityNode(VL::Ref<VL::Scene> Scene, VL::Entity Entity, const std::string& EntityName)
{
	ImGui::PushID((void*)Entity);

	bool Open = false;

	ImGuiTreeNodeFlags Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (Entity == _SelectedEntity)
	{
		Flags = Flags | ImGuiTreeNodeFlags_Selected;
	}

	Open = ImGui::TreeNodeEx((void*)Entity, Flags, EntityName.c_str());

	
	if (ImGui::IsItemClicked())
	{
		_SelectedEntity = Entity;
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
			Scene->DestroyEntity(Entity);
			EntityAlive = false;
		}

		ImGui::EndPopup();
	}

	ImGui::PopID();

	return EntityAlive;
}