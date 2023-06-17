#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

class InspectorWindow : public EditorWindow
{
public:

	void OnProcedure(const VL::Event& e) override;

	InspectorWindow(VL::Ref<EditorContext> context);

private:

	VL::Ref<VL::Material> m_SelectedMaterial;

	void EntityInspector();

	void MaterialInspector();

	template<typename T>
	bool ImGuiMaterialMap(std::map<std::string, T>& map, const std::vector<std::string>& blueprint, std::function<bool(const std::string&, T&)> drawFunc);

	template<typename T>
	void ImGuiComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc);
};

template<typename T>
inline bool InspectorWindow::ImGuiMaterialMap(std::map<std::string, T>& map, const std::vector<std::string>& blueprint, std::function<bool(const std::string&, T&)> drawFunc)
{
	bool changed = false;

	for (auto& [key, value] : map)
	{
		bool isInBlueprint = std::count(blueprint.begin(), blueprint.end(), key) != 0;

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

			if (drawFunc(name, value))
			{
				changed = true;
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
					map.erase(key);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Rename"))
				{
					changed = true;
					auto valueCopy = value;
					std::string newKey = VL::Dialog::InputBox("Rename Material Entry", "Please specify a new name");
					if (!newKey.empty())
					{
						map.erase(key);
						map[newKey] = valueCopy;
					}
				}

				ImGui::EndPopup();
			}
		}

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
	}	

	return changed;
}

template<typename T>
inline void InspectorWindow::ImGuiComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc)
{
	auto scene = this->m_Context->GetScene();

	for (int i = 0; i < scene->ComponentAmount<T>(entity); i++)
	{
		void* ptrID = scene->GetComponent<T>(entity, i).get();

		bool open = ImGui::TreeNodeEx(ptrID, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed, name.c_str());

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
			{
				scene->DeleteComponent<T>(entity, i);
			}

			ImGui::EndPopup();
		}

		if (open)
		{
			drawFunc(i);
			ImGui::TreePop();
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		}
	}
}