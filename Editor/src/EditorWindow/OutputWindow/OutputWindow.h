#pragma once

#include "../EditorWindow.h"

#include "EditorContext/EditorContext.h"

class OutputWindow : public EditorWindow
{
public:

	static void LoggerCallback(const std::string& string);

	void OnProcedure(const VL::Event& e) override;

	OutputWindow(VL::Ref<EditorContext> context);

private:

	static inline std::vector<std::string> m_TextList;

	static inline std::mutex m_Mutex;
};