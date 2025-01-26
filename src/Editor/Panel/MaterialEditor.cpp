#include "MaterialEditor.hpp"

#include "Editor.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void MaterialEditor::OnProcedure(const VL::Event& e)
{
	switch (e.type)
	{
	case VOLUND_EVENT_RENDER:
	{
		auto scene = this->m_context->state->SceneRef();
		auto state = this->m_context->state;

		std::shared_ptr<VL::Material> newMaterial = ImGuiAssetSelector("Material", this->m_selectedMaterial, this->m_context->state);
		if (newMaterial != nullptr)
		{
			this->m_selectedMaterial = newMaterial;
		}
		if (this->m_selectedMaterial == nullptr)
		{
			return;
		}

		ImVec2 listBoxSize = ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() + 10);
		if (ImGui::BeginListBox("##MaterialEditorShader", listBoxSize))
		{
			std::shared_ptr<VL::Shader> shader = this->m_selectedMaterial->GetShader();
			std::shared_ptr<VL::Shader> newShader = ImGuiAssetSelector("Shader", shader, this->m_context->state);
			if (newShader != nullptr)
			{
				this->m_selectedMaterial->SetShader(newShader);
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

				std::string coloredName;
				if (!isInBlueprint)
				{
					coloredName = VOLUND_LOGGERCOLOR_RED + uniformName;
				}
				else
				{
					coloredName = VOLUND_LOGGERCOLOR_BLUE + uniformName;
				}

				if (uniform->Is<VL::IntUniformType>())
				{
					if (ImGuiInt(coloredName, uniform->As<VL::IntUniformType>()))
					{
					}
				}
				else if (uniform->Is<VL::FloatUniformType>())
				{
					if (ImGuiFloat(coloredName, uniform->As<VL::FloatUniformType>()))
					{
					}
				}
				else if (uniform->Is<VL::DoubleUniformType>())
				{
					if (ImGuiDouble(coloredName, uniform->As<VL::DoubleUniformType>()))
					{
					}
				}
				else if (uniform->Is<VL::Vec2UniformType>())
				{
					if (ImGuiVec2(coloredName, uniform->As<VL::Vec2UniformType>()))
					{
					}
				}
				else if (uniform->Is<VL::Vec3UniformType>())
				{
					if (ImGuiVec3(coloredName, uniform->As<VL::Vec3UniformType>()))
					{
					}
				}
				else if (uniform->Is<VL::Vec4UniformType>())
				{
					if (ImGuiVec4(coloredName, uniform->As<VL::Vec4UniformType>()))
					{
					}
				}
				else if (uniform->Is<VL::TextureUniformType>())
				{
					std::shared_ptr<VL::Texture> newTexture = ImGuiAssetSelector(coloredName, uniform->As<VL::TextureUniformType>(), this->m_context->state);
					if (newTexture != nullptr)
					{
						this->m_selectedMaterial->Set(uniformName, newTexture);
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
						this->m_selectedMaterial->Erase(uniformName);
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
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
