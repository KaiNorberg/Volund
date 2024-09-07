#pragma once

#include "../EditorWindow.h"

class MaterialEditor : public EditorWindow
{
public:

    void OnProcedure(const VL::Event& e) override;

    MaterialEditor(VL::Ref<EditorContext> context);

private:

    VL::Ref<VL::Material> m_SelectedMaterial;
};