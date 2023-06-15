#pragma once

#include "EditorContext/EditorContext.h"

class AddComponentPopup : public VL::ImGuiObject
{
public:

	void Open();

	void Procedure(const VL::Event& e) override;

	AddComponentPopup(VL::Ref<EditorContext> context);

private:

	bool m_ShouldOpen = false;

	VL::Ref<EditorContext> m_Context;
}; 