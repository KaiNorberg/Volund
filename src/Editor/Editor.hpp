#pragma once

#include "EditorContext.hpp"

#include "Panel/Panel.hpp"

class Editor : public VL::Application
{
public:
    void Procedure(const VL::Event& e) override;
    Editor();
    virtual ~Editor();
private:
    bool BeginDockSpace();
    void DrawBackground();
    std::shared_ptr<EditorContext> m_context;
    std::vector<std::shared_ptr<Panel>> m_panels;
    VL::Input m_input;
};
