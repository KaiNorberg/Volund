#pragma once

#include "Panel.h"

#include <imgui.h>

class Inspector : public Panel
{
public:

    void OnProcedure(const VL::Event& e) override;

    Inspector(std::shared_ptr<EditorContext> context);

private:

    template<typename T>
    void ImGuiComponent(std::string const& name, VL::Entity entity, std::function<void(int)> drawFunc);
};

template<typename T>
inline void Inspector::ImGuiComponent(std::string const& name, VL::Entity entity, std::function<void(int)> drawFunc)
{
    auto scene = this->m_context->state->SceneRef();

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
