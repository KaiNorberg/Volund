#pragma once

#include "Panel.h"

class MaterialEditor : public Panel
{
public:

    void OnProcedure(const VL::Event& e) override;

    MaterialEditor(std::shared_ptr<EditorContext> context);

private:

    std::shared_ptr<VL::Material> m_selectedMaterial;
};
