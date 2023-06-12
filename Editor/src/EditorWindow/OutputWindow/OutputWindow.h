#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

class OutputWindow : public EditorWindow
{
public:

	static void LoggerCallback(const std::string& string);

	OutputWindow(VL::Ref<EditorContext> context);

private:

	float m_TotalTime = 0.0f;

	static inline VL::Ref<VL::ImGuiTextList> m_TextList = std::make_shared<VL::ImGuiTextList>();

	static inline std::mutex m_Mutex;
};