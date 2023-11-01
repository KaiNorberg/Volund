#pragma once

#include "../EditorWindow.h"

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
	auto gameState = this->m_Context->GameState;

	for (int i = 0; i < gameState->ComponentAmount<T>(entity); i++)
	{
		void* ptrID = gameState->GetComponent<T>(entity, i).get();

		bool open = ImGui::TreeNodeEx(ptrID, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed, name.c_str());

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
			{
				gameState->DeleteComponent<T>(entity, i);
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