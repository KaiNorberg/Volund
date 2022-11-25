#pragma once

class Widget
{
public:

	virtual const char* GetName() = 0;

	virtual void OnEvent(VL::Event* E) {}

	virtual void OnUpdate(VL::TimeStep TS) {}

	bool IsActive = true;

protected:
	
	void DrawText(const std::string& String);
};