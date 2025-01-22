#pragma once

#include "Panel.hpp"

class Hierarchy : public Panel
{
public:

    void OnProcedure(const VL::Event& e) override;

    Hierarchy(std::shared_ptr<EditorContext> context);

private:

    std::shared_ptr<EditorContext> m_context;

    bool ImGuiEntity(VL::Entity Entity, std::string const& EntityName);
};
