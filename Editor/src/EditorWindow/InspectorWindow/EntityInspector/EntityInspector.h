#pragma once

#include "EditorContext/EditorContext.h"

class EntityInspector : public VL::ImGuiObject
{
public:

	void Procedure(const VL::Event& e) override;

	EntityInspector(VL::Ref<EditorContext> context);

private:

	template<typename T>
	void DrawComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc);

	VL::Ref<EditorContext> m_Context;
}; 

template<typename T>
inline void EntityInspector::DrawComponent(const std::string& name, VL::Entity entity, std::function<void(int)> drawFunc)
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