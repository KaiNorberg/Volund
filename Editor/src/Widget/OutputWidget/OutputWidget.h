#pragma once

#include "Widget/Widget.h"

class OutputWidget : public Widget
{
public:

	const char* GetName();

	void OnEvent(VL::Event* E);

	void OnUpdate(VL::TimeStep TS);

	static void LoggerCallback(const std::string& String);

	OutputWidget();

private:

	static inline std::vector<std::string> _Output;
};

