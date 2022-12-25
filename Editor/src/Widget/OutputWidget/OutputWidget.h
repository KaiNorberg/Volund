#pragma once

#include "Widget/Widget.h"

class OutputWidget : public Widget
{
public:

	const char* GetName();

	void OnUpdate(VL::TimeStep TS) override;

	void OnRender() override;

	static void LoggerCallback(const std::string& String);

	OutputWidget(VL::Application* App);

private:

	float TotalTime = 0.0f;

	static inline std::mutex _Mutex;

	static inline std::vector<std::string> _Output;
};

