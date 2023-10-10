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

		if (ImGuiMaterialMap<int>(this->m_SelectedMaterial->IntMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Int), ImGuiInt))
		{
			changed = true;
		}

		if (ImGuiMaterialMap<double>(this->m_SelectedMaterial->DoubleMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Double), ImGuiDouble))
		{
			changed = true;
		}

		if (ImGuiMaterialMap<VL::Vec2>(this->m_SelectedMaterial->Vec2Map(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Vec2),
			[](const std::string& key, VL::Vec2& value) { return ImGuiVec2(key, value); }))
		{
			changed = true;
		}

		if (ImGuiMaterialMap<VL::Vec3>(this->m_SelectedMaterial->Vec3Map(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Vec3),
			[](const std::string& key, VL::Vec3& value) { return ImGuiVec3(key, value); }))
		{
			changed = true;
		}

		if (ImGuiMaterialMap<VL::Vec4>(this->m_SelectedMaterial->Vec4Map(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Vec4),
			[](const std::string& key, VL::Vec4& value) { return ImGuiVec4(key, value); }))
		{
			changed = true;
		}

		if (ImGuiMaterialMap<VL::Ref<VL::Texture>>(this->m_SelectedMaterial->TextureMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Sampler),
			[assetManager](const std::string& key, VL::Ref<VL::Texture>& value)
			{
				std::string texturePath = assetManager->FetchFilepath<VL::Texture>(value);
				if (ImGuiFile(key, texturePath))
				{
					value = assetManager->Fetch<VL::Texture>(texturePath);
					return true;
				}
				else
				{
					return false;
				}
			}))
		{
			changed = true;
		}

		ImGuiAlign("Add Entry", 0.5f);
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
			if (ImGui::MenuItem("Double"))
			{
				changed = true;
				this->m_SelectedMaterial->SetDouble("NewDouble", 0.0);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Vec2"))
			{
				changed = true;
				this->m_SelectedMaterial->SetVec2("NewVec2", VL::Vec2(0.0f, 0.0f));
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
				this->m_SelectedMaterial->SetTexture("NewTexture", nullptr);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (changed && this->m_Context->IsPaused())
		{
			assetManager->Serialize(this->m_SelectedMaterial, materialPath);
		}
	}
	break;
	case EDITOR_EVENT_TYPE_LOAD_SCENE:
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