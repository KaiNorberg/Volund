#pragma once

#include "EditorContext/EditorContext.h"

class Editor : public VL::Application
{
public:

	void OnRun() override;

	void OnTerminate() override;

	void Procedure(const VL::Event& e) override;

	virtual ~Editor() = default;

private:

	void BackgroundCallback();

	bool m_iniLoaded = false;

	VL::Input m_Input;
};

