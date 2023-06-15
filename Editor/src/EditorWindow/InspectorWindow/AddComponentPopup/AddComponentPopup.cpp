#include "PCH/PCH.h"
#include "AddComponentPopup.h"

#include "Utils/Utils.h"

void AddComponentPopup::Open()
{
	this->m_ShouldOpen = true;
	this->IsActive = true;
}

void AddComponentPopup::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::Render:
	{
		//IMPORTANT: Remember to update the code below whenever a new component is implemented.
		auto scene = this->m_Context->GetScene();
		auto selectedEntity = this->m_Context->SelectedEntity;

		if (scene == nullptr)
		{
			break;
		}

		if (ImGui::BeginPopup("Add Component"))
		{
			if (ImGui::MenuItem("Tag"))
			{
				scene->CreateComponent<VL::Tag>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("Transform"))
			{
				scene->CreateComponent<VL::Transform>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("Camera"))
			{
				scene->CreateComponent<VL::Camera>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("MeshRenderer"))
			{
				scene->CreateComponent<VL::MeshRenderer>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("PointLight"))
			{
				scene->CreateComponent<VL::PointLight>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("CameraMovement"))
			{
				scene->CreateComponent<VL::CameraMovement>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("SoundSource"))
			{
				scene->CreateComponent<VL::SoundSource>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}
			if (ImGui::MenuItem("SoundListener"))
			{
				scene->CreateComponent<VL::SoundListener>(selectedEntity);
				ImGui::CloseCurrentPopup();
				this->IsActive = false;
			}

			ImGui::EndPopup();
		}

		if (this->m_ShouldOpen)
		{
			ImGui::OpenPopup("Add Component");
			this->m_ShouldOpen = false;
		}
	}
	break;
	case VL::EventType::Update:
	{
	}
	break;
	}
}

AddComponentPopup::AddComponentPopup(VL::Ref<EditorContext> context)
{
	this->m_Context = context;
	this->IsActive = false;
}