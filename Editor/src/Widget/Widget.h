#pragma once

class Widget
{
public:

	bool _IsActive = false;

	virtual const char* GetName() = 0;

	virtual void OnUpdate() = 0;

	virtual ~Widget() = default;

protected:

	static void Align(float Width, float Alignment);

	static std::string TextSelectorControl(const std::string& Name, const std::string& Default, const std::vector<std::string>& SelectableValues);

	static std::string TextControl(const std::string& Name, const std::string& Default);

	static void BoolControl(const std::string& Name, bool* Value);

	static void FloatControl(const std::string& Name, float* Value);

	static void Vec3Control(std::string_view Name, Volund::Vec3* Value, float Speed = 0.1f, float DefaultValue = 0.0f);

	Volund::Layer* _Parent = nullptr;
};
