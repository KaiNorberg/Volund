#pragma once

class Widget
{
public:

	bool _IsActive = false;

	virtual const char* GetName() = 0;

	virtual void OnUpdate() = 0;

	virtual ~Widget() = default;

protected:

	void DrawVec3Control(std::string_view Name, Volund::Vec3& Value, float Speed = 0.1f, float DefaultValue = 0.0f);

	Volund::Layer* _Parent = nullptr;
};

