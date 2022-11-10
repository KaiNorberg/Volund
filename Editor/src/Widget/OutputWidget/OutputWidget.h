#pragma once

#include "Widget/Widget.h"

class OutputWidget : public Widget
{
public:

	const char* GetName() override;

	void Draw(VL::TimeStep TS) override;

	static void LoggerCallback(const std::string& String);

	OutputWidget(Editor* editor, bool Active = false);

private:

	static inline std::vector<std::string> _Output;
};

