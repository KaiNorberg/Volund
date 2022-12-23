#pragma once

class Widget
{
public:

	virtual const char* GetName() = 0;

	virtual void OnKey(const VL::Event& E) {}

	virtual void OnUpdate(VL::TimeStep TS) {}

	virtual void OnRender() {}

	bool IsActive = true;

protected:
	
	void DrawText(const std::string& String);

	VL::Application* _App = nullptr;
};