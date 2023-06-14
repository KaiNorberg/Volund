#include "PCH/PCH.h"
#include "EntityHierarchy.h"

#include "Utils/Utils.h"

void EntityHierarchy::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		auto scene = this->m_Context->GetScene();

		std::string scenePath = this->m_Context->GetScenePath();
		if (Utils::ImGuiFile("Scene", scenePath))
		{
			this->m_Context->LoadScene(this->m_Context->GetParentPath() + "/" + scenePath);
		}

		if (scene != nullptr)
		{
			for (auto& [entity, container] : *scene)
			{
				std::string entityName = "#" + std::to_string(entity);
				if (scene->HasComponent<VL::Tag>(entity))
				{
					entityName += " | " + scene->GetComponent<VL::Tag>(entity)->String;
				}

				if (entityName.find(this->m_Filter) != std::string::npos)
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
	case VL::EventType::Update:
	{
	}
	break;
	}
}

bool EntityHierarchy::ImGuiEntity(VL::Entity entity, const std::string& entityName)
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

EntityHierarchy::EntityHierarchy(VL::Ref<EditorContext> context)
{
	this->m_Context = context;
}