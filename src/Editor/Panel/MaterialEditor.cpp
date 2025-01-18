#include "MaterialEditor.h"

#include "Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void MaterialEditor::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		auto gameState = this->m_context->GameState;

		std::string materialPath = gameState->FetchFilepath<VL::Material>(this->m_selectedMaterial);
		if (ImGuiFile("Material/Effect", materialPath))
		{
			this->m_selectedMaterial = gameState->FetchAsset<VL::Material>(materialPath);
		}
		ImGui::Separator();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

		if (this->m_selectedMaterial == nullptr)
		{
			ImGui::Text("Invalid material!");
			return;
		}

		bool changed = false;

		ImVec2 listBoxSize = ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() + 10);
		if (ImGui::BeginListBox("##MaterialEditorShader", listBoxSize))
		{
			std::string shaderPath = gameState->FetchFilepath<VL::Shader>(this->m_selectedMaterial->GetShader());
			if (ImGuiFile("Shader", shaderPath))
			{
				changed = true;
				this->m_selectedMaterial->SetShader(gameState->FetchAsset<VL::Shader>(shaderPath));
			}

			ImGui::EndListBox();
		}

		auto materialBlueprint = this->m_selectedMaterial->GetBlueprint();
		if (materialBlueprint == nullptr)
		{
			ImGui::Text("Material is missing a shader or a blueprint!");
			return;
		}

		for (auto& uniform : (*this->m_selectedMaterial))
		{
			std::string uniformName = uniform->GetName();

			bool isInBlueprint = materialBlueprint->Contains(uniformName);

			ImVec2 itemRectMin;
			ImVec2 itemRectMax;
			ImVec2 listBoxSize = ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() + 10);
			if (ImGui::BeginListBox((std::string("##ListBox") + uniformName).c_str(), listBoxSize))
			{
				itemRectMin = ImVec2(ImGui::GetWindowPos().x, ImGui::GetItemRectMin().y);
				itemRectMax = ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, itemRectMin.y + listBoxSize.y);

				std::string name;
				if (!isInBlueprint)
				{
					name = uniformName;
				}
				else
				{
					name = VOLUND_LOGGERCOLOR_BLUE + uniformName;
				}

				if (uniform->Is<VL::IntUniformType>())
				{
					if (ImGuiInt(name, uniform->As<VL::IntUniformType>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::FloatUniformType>())
				{
					if (ImGuiFloat(name, uniform->As<VL::FloatUniformType>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::DoubleUniformType>())
				{
					if (ImGuiDouble(name, uniform->As<VL::DoubleUniformType>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::Vec2UniformType>())
				{
					if (ImGuiVec2(name, uniform->As<VL::Vec2UniformType>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::Vec3UniformType>())
				{
					if (ImGuiVec3(name, uniform->As<VL::Vec3UniformType>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::Vec4UniformType>())
				{
					if (ImGuiVec4(name, uniform->As<VL::Vec4UniformType>()))
					{
						changed = true;
					}
				}
				else if (uniform->Is<VL::TextureUniformType>())
				{
					std::string texturePath = gameState->FetchFilepath<VL::Texture>(uniform->As<VL::TextureUniformType>());
					if (ImGuiFile(name, texturePath))
					{
						this->m_selectedMaterial->Set(uniformName, gameState->FetchAsset<VL::Texture>(texturePath));
						changed = true;
					}
				}
				else
				{
					VOLUND_INFO("Invalid Uniform Type!");
				}

				ImGui::EndListBox();
			}

			if (!isInBlueprint)
			{
				std::string popupName = (std::string("Material entry") + uniformName);

				if (ImGui::IsMouseHoveringRect(itemRectMin, itemRectMax) && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				{
					ImGui::OpenPopup(popupName.c_str());
				}

				if (ImGui::BeginPopup(popupName.c_str()))
				{
					if (ImGui::MenuItem("Delete"))
					{
						changed = true;
						this->m_selectedMaterial->Erase(uniformName);
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		}

		if (changed && this->m_context->IsPaused())
		{
			gameState->Serialize(this->m_selectedMaterial, materialPath);
		}
	}
	break;
	case EDITOR_EVENT_RESET:
	{
		this->m_selectedMaterial = nullptr;
	}
	break;
	}
}

MaterialEditor::MaterialEditor(std::shared_ptr<EditorContext> context)
{
	this->SetName("Material/Effect Editor");

	this->m_context = context;
}
