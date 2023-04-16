#pragma once

#include "Widget/Widget.h"

#include "Editor/EditorModule/EditorModule.h"

class InspectorWidget : public Widget
{
public:

	const char* GetName() override;

	void OnRender() override;

	InspectorWidget(VL::Application* app);

private:

	template<typename T>
	void DrawComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc);

	void DrawComponents();

	void DrawAddComponents();

	VL::Entity m_SelectedEntity = 3;
};

template<typename T>
inline void InspectorWidget::DrawComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc)
{
	auto scene = this->m_App->GetModule<EditorModule>()->GetScene();

	for (int i = 0; i < scene->ComponentAmount<T>(entity); i++)
	{
		void* ptrID = scene->GetComponent<T>(entity, i).get();

		bool Open = ImGui::TreeNodeEx(ptrID, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed, name.c_str());

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
			{
				scene->DeleteComponent<T>(entity, i);
			}

			ImGui::EndPopup();
		}

		if (Open)
		{
			drawFunc(i);
			ImGui::TreePop();
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		}
	}
}
