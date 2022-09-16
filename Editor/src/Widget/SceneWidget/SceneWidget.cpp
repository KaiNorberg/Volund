#include "PCH/PCH.h"
#include "SceneWidget.h"

#include <imgui.h>

#include "Editor/EditorLayer/EditorLayer.h"

const char* SceneWidget::GetName()
{
	return "Scene";
}

void SceneWidget::OnUpdate()
{
	auto Scene = this->_Parent->GetLayer<EditorLayer>()->GetScene();

	if (ImGui::Begin("Scene", &this->_IsActive))
	{
		char SearchTerm[64];
		ImGui::Text("Search: ");
		ImGui::SameLine();
		ImGui::InputText(" ", SearchTerm, 64);

		if (ImGui::BeginListBox(" ", ImVec2(-FLT_MIN, -ImGui::GetContentRegionAvail().y / 2)))
		{
			if (Scene != nullptr)
			{
				for (auto Entity : (*Scene.get()))
				{
					if (Entity->GetName().find(SearchTerm) != std::string::npos)
					{
						this->DrawEntity(Entity);
					}
				}
			}

			ImGui::EndListBox();
		}

		if (Scene->HasEntity(this->_SelectedEntity))
		{
			auto Entity = Scene->GetEntity(this->_SelectedEntity);

			this->DrawComponents(Entity);
		}
	}

	ImGui::End();
}

void SceneWidget::DrawEntity(Volund::Ref<Volund::Entity> Entity)
{
	std::string EntityName = Entity->GetName();

	bool Open = false;
	if (EntityName == _SelectedEntity)
	{
		Open = ImGui::TreeNodeEx((void*)Entity.get(), ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow, EntityName.c_str());
	}
	else
	{
		Open = ImGui::TreeNodeEx((void*)Entity.get(), ImGuiTreeNodeFlags_OpenOnArrow, EntityName.c_str());
	}

	if (ImGui::IsItemClicked())
	{
		_SelectedEntity = EntityName;
	}

	if (Open)
	{
		ImGui::TreePop();
	}
}

void SceneWidget::DrawComponents(Volund::Ref<Volund::Entity> Entity)
{
	if (Entity->HasComponent<Transform>())
	{
		auto& View = Entity->ComponentView<Volund::Transform>();
		for (auto& Component : View)
		{
			auto Transform = std::dynamic_pointer_cast<Volund::Transform>(Component);

			if (ImGui::TreeNodeEx((void*)Transform.get(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed, "Transform"))
			{
				auto Transform = std::dynamic_pointer_cast<Volund::Transform>(Component);
				Volund::Vec3 Position = Transform->Position;
				Volund::Vec3 Rotation = Transform->GetRotation();
				Volund::Vec3 Scale = Transform->Scale;

				this->DrawVec3Control("Position", Position, 0.1f, 0.0f);
				this->DrawVec3Control("Rotation", Rotation, 0.1f, 0.0f);
				this->DrawVec3Control("Scale", Scale, 0.1f, 1.0f);

				Transform->Position = Position;
				Transform->SetRotation(Rotation);
				Transform->Scale = Scale;

				ImGui::TreePop();
			}
		}
	}
}

SceneWidget::SceneWidget(Volund::Layer* Parent)
{
	this->_Parent = Parent;
}
