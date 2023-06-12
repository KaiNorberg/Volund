#pragma once

#include "EditorContext/EditorContext.h"

class EntityHierarchy : public VL::ImGuiObject
{
public:

	void Procedure(const VL::Event& e) override;

	EntityHierarchy(VL::Ref<EditorContext> context);

private:

	std::string m_Filter;

	VL::Ref<EditorContext> m_Context;

	bool ImGuiEntity(VL::Entity Entity, const std::string& EntityName);
}; 