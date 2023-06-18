#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

class InspectorWindow : public EditorWindow
{
public:

	void OnProcedure(const VL::Event& e) override;

	InspectorWindow(VL::Ref<EditorContext> context);

private:

	template<typename T>
	void ImGuiComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc);
};

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