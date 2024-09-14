#pragma once

#include "Panel.h"

class Hierarchy : public Panel
{
public:

    void OnProcedure(const VL::Event& e) override;

    Hierarchy(std::shared_ptr<EditorContext> context);

private:

    std::shared_ptr<EditorContext> m_Context;

    bool ImGuiEntity(VL::Entity Entity, const std::string& EntityName);
};
