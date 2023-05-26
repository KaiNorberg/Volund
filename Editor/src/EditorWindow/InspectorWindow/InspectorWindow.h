#pragma once

#include "../EditorWindow.h"

class InspectorWindow : public EditorWindow
{
public:

	const char* GetName() override;

	InspectorWindow(VL::Ref<EditorContext> context);

private:

};
