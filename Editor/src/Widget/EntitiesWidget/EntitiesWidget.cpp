#include "PCH/PCH.h"
#include "EntitiesWidget.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* EntitiesWidget::GetName()
{
	return "Entities";
}

void EntitiesWidget::OnUpdate(TimeStep TS)
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

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
					if (Scene->HasComponent<Volund::Tag>(Entity))
					{
						EntityName += " | " + Scene->GetComponent<Volund::Tag>(Entity)->String;
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
			ImGui::Text("No Scene Loaded!");
		}
	}

	ImGui::End();
}

bool EntitiesWidget::DrawEntityNode(Volund::Ref<Volund::Scene> Scene, Volund::Entity Entity, const std::string& EntityName)
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

EntitiesWidget::EntitiesWidget(Volund::Layer* Parent, bool Active)
{
	this->_Parent = Parent;
	this->_IsActive = Active;
}
