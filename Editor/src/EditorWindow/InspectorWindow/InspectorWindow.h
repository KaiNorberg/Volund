#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

#include "AddComponentPopup/AddComponentPopup.h"

class InspectorWindow : public EditorWindow
{
public:

	InspectorWindow(VL::Ref<EditorContext> context);

private:

	VL::Ref<AddComponentPopup> m_AddComponentPopup;
};
