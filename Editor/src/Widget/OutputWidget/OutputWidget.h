#pragma once

#include "Widget/Widget.h"

class OutputWidget : public Widget
{
public:

	const char* GetName() override;

	void Procedure(const VL::Event& e) override;

	static void LoggerCallback(const std::string& string);

	OutputWidget(VL::Ref<EditorContext> context);

private:

	float m_TotalTime = 0.0f;

	static inline std::mutex m_Mutex;

	static inline std::vector<std::string> m_Output;
};

