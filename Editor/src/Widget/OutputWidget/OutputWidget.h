#pragma once

#include "Widget/Widget.h"

class OutputWidget : public Widget
{
public:

	const char* GetName() override;

	void OnUpdate(VL::TimeStep ts) override;

	void OnRender() override;

	static void LoggerCallback(const std::string& string);

	OutputWidget(VL::Application* app);

private:

	float m_TotalTime = 0.0f;

	static inline std::mutex m_Mutex;

	static inline std::vector<std::string> m_Output;
};

