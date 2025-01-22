#include "Hierarchy.h"

#include <imgui.h>

void Hierarchy::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		auto scene = this->m_context->state->SceneRef();

		if (ImGui::Button("+"))
		{
			scene->Register();
		}

		ImGui::SameLine();
		static char searchTerm[64];
		ImGui::Text("Search: ");
		ImGui::SameLine();
		ImGui::InputText(" ", searchTerm, 64);

		for (auto& EntityEntry : *scene)
		{
			VL::Entity entity = EntityEntry.Get();
			std::string entityName;
			if (scene->HasComponent<VL::Tag>(entity))
			{
				entityName = scene->GetComponent<VL::Tag>(entity)->string;
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

bool Hierarchy::ImGuiEntity(VL::Entity entity, std::string const& entityName)
{
	auto scene = this->m_context->state->SceneRef();
	auto& selectedEntity = this->m_context->selectedEntity;

	ImGui::PushID((void*)entity.AsInt());

	bool open = false;

	ImGuiTreeNodeFlags Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (entity == selectedEntity)
	{
		Flags = Flags | ImGuiTreeNodeFlags_Selected;
	}

	open = ImGui::TreeNodeEx((void*)entity.AsInt(), Flags, entityName.c_str());

	if (ImGui::IsItemClicked())
	{
		selectedEntity = entity;
	}

	if (open)
	{
		ImGui::TreePop();
	}

	bool entityAlive = true;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete"))
		{
			scene->Unregister(entity);
			entityAlive = false;
		}

		ImGui::EndPopup();
	}

	ImGui::PopID();

	return entityAlive;
}

Hierarchy::Hierarchy(std::shared_ptr<EditorContext> context)
{
	this->SetName("Hierarchy");

	this->m_context = context;
}
