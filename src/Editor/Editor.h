#pragma once

#include "EditorContext.h"

#include "Panel/Panel.h"

class Editor : public VL::Application
{
public:

    void OnRun() override;

    void OnTerminate() override;

    void Procedure(const VL::Event& e) override;

    virtual ~Editor() = default;

private:

    bool BeginDockSpace();

    void DrawBackground();

    std::shared_ptr<EditorContext> m_Context;
    std::vector<std::shared_ptr<Panel>> m_Panels;
    VL::Input m_Input;
};
