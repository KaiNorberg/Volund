#include "PCH/PCH.h"

#include "MaterialEditor.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void MaterialEditor::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		auto assetManager = this->m_Context->GetAssetmanager();
		if (assetManager == nullptr)
		{
			ImGui::Text("No Scene Loaded!");
			return;
		}

		std::string materialPath = assetManager->FetchFilepath<VL::Material>(this->m_SelectedMaterial);
		if (ImGuiFile("Material/Effect", materialPath))
		{
			this->m_SelectedMaterial = assetManager->Fetch<VL::Material>(materialPath);
		}
		ImGui::Separator();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

		if (this->m_SelectedMaterial == nullptr)
		{
			ImGui::Text("Invalid material!");
			return;
		}

		bool changed = false;

		ImVec2 listBoxSize = ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() + 10);
		if (ImGui::BeginListBox("##MaterialEditorShader", listBoxSize))
		{
			std::string shaderPath = assetManager->FetchFilepath<VL::Shader>(this->m_SelectedMaterial->GetShader());
			if (ImGuiFile("Shader", shaderPath))
			{
				changed = true;
				this->m_SelectedMaterial->SetShader(assetManager->Fetch<VL::Shader>(shaderPath));
			}

			ImGui::EndListBox();
		}

		auto materialBlueprint = this->m_SelectedMaterial->GetBlueprint();
		if (materialBlueprint == nullptr)
		{
			ImGui::Text("Material is missing a shader or a blueprint!");
			return;
		}

		for (auto& [key, uniform] : (*this->m_SelectedMaterial))
		{
			bool isInBlueprint = materialBlueprint->Exists(key);

			ImVec2 itemRectMin;
			ImVec2 itemRectMax;
			ImVec2 listBoxSize = ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() + 10);
			if (ImGui::BeginListBox((std::string("##ListBox") + key).c_str(), listBoxSize))
			{
				itemRectMin = ImVec2(this->GetPosition().x, ImGui::GetItemRectMin().y);
				itemRectMax = ImVec2(this->GetPosition().x + this->GetSize().x, itemRectMin.y + listBoxSize.y);

				std::string name;
				if (!isInBlueprint)
				{
					name = key;
				}
				else
				{
					name = VOLUND_LOGGERCOLOR_BLUE + key;
				}

				if (uniform->Is<VL::UniformInt>())
				{
					if (ImGuiInt(name, *uniform->Get<VL::UniformInt>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::UniformFloat>())
				{
					if (ImGuiFloat(name, *uniform->Get<VL::UniformFloat>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::UniformDouble>())
				{
					if (ImGuiDouble(name, *uniform->Get<VL::UniformDouble>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::UniformVec2>())
				{
					if (ImGuiVec2(name, *uniform->Get<VL::UniformVec2>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::UniformVec3>())
				{
					if (ImGuiVec3(name, *uniform->Get<VL::UniformVec3>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::UniformVec4>())
				{
					if (ImGuiVec4(name, *uniform->Get<VL::UniformVec4>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::UniformTexture>())
				{
					std::string texturePath = assetManager->FetchFilepath<VL::Texture>(uniform->As<VL::UniformTexture>());
					if (ImGuiFile(name, texturePath))
					{
						this->m_SelectedMaterial->Set(key, assetManager->Fetch<VL::Texture>(texturePath));
						changed = true;
					}
				}

				ImGui::EndListBox();
			}

			if (!isInBlueprint)
			{
				std::string popupName = (std::string("Material entry") + key);

				if (ImGui::IsMouseHoveringRect(itemRectMin, itemRectMax) && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				{
					ImGui::OpenPopup(popupName.c_str());
				}

				if (ImGui::BeginPopup(popupName.c_str()))
				{
					if (ImGui::MenuItem("Delete"))
					{
						changed = true;
						this->m_SelectedMaterial->Erase(key);
						ImGui::CloseCurrentPopup();
					}
					if (ImGui::MenuItem("Rename"))
					{
						changed = true;
						std::string newKey = VL::Dialog::InputBox("Rename Material Entry", "Please specify a new name");
						if (!newKey.empty())
						{
							this->m_SelectedMaterial->Rename(key, newKey);
						}
					}

					ImGui::EndPopup();
				}
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		}

		//Temporarily disabled
		/*ImGuiAlign("Add Entry", 0.5f);
		if (ImGui::Button("Add Entry"))
		{
			ImGui::OpenPopup("Add Entry");
		}

		if (ImGui::BeginPopup("Add Entry"))
		{
			if (ImGui::MenuItem("Int"))
			{
				changed = true;
				this->m_SelectedMaterial->SetInt("NewInt", 0);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Float"))
			{
				changed = true;
				this->m_SelectedMaterial->SetFloat("NewDouble", 0.0);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Vec2"))
			{
				changed = true;
				this->m_SelectedMaterial->SetVec2("NewVec2", VL::UniformVec2(0.0f, 0.0f));
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Vec3"))
			{
				changed = true;
				this->m_SelectedMaterial->SetVec3("NewVec3", VL::Vec3(0.0f, 0.0f, 0.0f));
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Vec4"))
			{
				changed = true;
				this->m_SelectedMaterial->SetVec4("NewVec4", VL::Vec4(0.0f, 0.0f, 0.0f, 0.0f));
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Texture"))
			{
				changed = true;
				this->m_SelectedMaterial->SetTexture("NewTexture", VL::Ref<VL::Texture>(nullptr));
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}*/

		if (changed && this->m_Context->IsPaused())
		{
			assetManager->Serialize(this->m_SelectedMaterial, materialPath);
		}
	}
	break;
	case EDITOR_EVENT_TYPE_RESET:
	{
		this->m_SelectedMaterial = nullptr;
	}
	break;
	}
}

MaterialEditor::MaterialEditor(VL::Ref<EditorContext> context)
{
	this->SetName("Material/Effect Editor");

	this->m_Context = context;
}