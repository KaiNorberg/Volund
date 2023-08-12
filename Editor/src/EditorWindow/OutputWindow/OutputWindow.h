#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

class OutputWindow : public EditorWindow
{
public:

	void OnProcedure(const VL::Event& e) override;

	OutputWindow(VL::Ref<EditorContext> context);

private:
};