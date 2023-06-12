#include "PCH/PCH.h"

#include "InspectorWindow.h"

#include "Editor/Editor.h"

#include "EntityInspector/EntityInspector.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

/*void InspectorWindow::DrawAddComponents()
{
	auto scene = this->m_Context->GetScene();
	auto selectedEntity = this->m_Context->SelectedEntity;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

	Align(ImGui::CalcTextSize("Add Component").x, 0.5f);
	if (ImGui::Button("Add Component"))
	{
		ImGui::OpenPopup("Add Component");
	}

	if (ImGui::BeginPopup("Add Component"))
	{
		if (ImGui::MenuItem("Tag"))
		{
			scene->CreateComponent<VL::Tag>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Transform"))
		{
			scene->CreateComponent<VL::Transform>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			scene->CreateComponent<VL::Camera>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("MeshRenderer"))
		{
			scene->CreateComponent<VL::MeshRenderer>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("PointLight"))
		{
			scene->CreateComponent<VL::PointLight>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("CameraMovement"))
		{
			scene->CreateComponent<VL::CameraMovement>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("SoundSource"))
		{
			scene->CreateComponent<VL::SoundSource>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("SoundListener"))
		{
			scene->CreateComponent<VL::SoundListener>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}*/

/*void InspectorWindow::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		if (ImGui::Begin(this->GetName(), &this->IsActive))
		{
			auto scene = this->m_Context->GetScene();
			auto selectedEntity = this->m_Context->SelectedEntity;

			if (scene != nullptr && scene->IsEntityRegistered(selectedEntity))
			{
				ImGui::Separator();

				this->DrawComponents();

				ImGui::Separator();

				this->DrawAddComponents();
			}
			else
			{
				ImGui::Text("No Entity Selected!");
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
}*/

InspectorWindow::InspectorWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Inspector");

	this->m_Context = context;

	//this->PushObject(VL::Ref<VL::ImGuiSeparator>(new VL::ImGuiSeparator("InspectorUpperSeperator")));

	auto tabBar = VL::Ref<VL::ImGuiTabBar>(new VL::ImGuiTabBar());

	tabBar->PushObject("EntityInspector", VL::Ref<EntityInspector>(new EntityInspector(this->m_Context)));

	this->PushObject(tabBar);

	this->PushObject(VL::Ref<VL::ImGuiSeparator>(new VL::ImGuiSeparator()));

	//this->PushObject(VL::Ref<VL::ImGuiButton>(new VL::ImGuiButton("AddComponentButton")));
}

