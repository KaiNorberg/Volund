#pragma once

class Widget
{
public:

	virtual const char* GetName() = 0;

	virtual void OnKey(const VL::Event& e) {}

	virtual void OnUpdate(VL::TimeStep ts) {}

	virtual void OnRender() {}

	bool IsActive = true;

protected:
	
	void DrawText(const std::string& string);

	VL::Application* m_App = nullptr;
};