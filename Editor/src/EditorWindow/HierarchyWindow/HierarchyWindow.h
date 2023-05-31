#pragma once

#include "../EditorWindow.h"

#include "EntityHierarchy/EntityHierarchy.h"

class HierarchyWindow : public EditorWindow
{
public:

	HierarchyWindow(VL::Ref<EditorContext> context);

private:

	VL::Ref<EntityHierarchy> m_EntityHierarchy;
};

