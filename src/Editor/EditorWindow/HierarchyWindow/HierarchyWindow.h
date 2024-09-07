#pragma once

#include "../EditorWindow.h"

class HierarchyWindow : public EditorWindow
{
public:

    void OnProcedure(const VL::Event& e) override;

    HierarchyWindow(VL::Ref<EditorContext> context);

private:
    
    VL::Ref<EditorContext> m_Context;

    bool ImGuiEntity(VL::Entity Entity, const std::string& EntityName);
};

