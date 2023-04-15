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
	
	static void StartCombo();

	static void NextColumn();

	static void EndCombo();

	static void Align(float Width, float Alignment);

	static void DrawText(const std::string& String);

	static std::string TextSelectorControl(const std::string& Name, const std::string& Default, const std::vector<std::string>& SelectableValues);

	static std::string TextControl(const std::string& Name, const std::string& Default);

	static std::string FileSelectorControl(const std::string& Name, const std::string& Default, VL::Ref<VL::Window> Owner);

	static void BoolControl(const std::string& Name, bool* Value);

	static void FloatControl(const std::string& Name, float* Value);

	static void Vec3Control(std::string_view Name, VL::Vec3* Value, float Speed = 0.1f, float DefaultValue = 0.0f);

	static VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize);

	VL::Application* m_App = nullptr;
};