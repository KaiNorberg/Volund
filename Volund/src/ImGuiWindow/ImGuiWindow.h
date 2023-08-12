#pragma once

#include "Dispatcher/Event/Event.h"
#include "PolyContainer/PolyContainer.h"

#define VOLUND_IMGUI_FILE "VOLUND_IMGUI_FILE"
#define VOLUND_IMGUI_DIRECTORY "VOLUND_IMGUI_DIRECTORY"

namespace Volund
{
	class ImGuiWindow
	{
	public:

		bool IsActive = true;

		bool IsWindowHovered();

		void SetSize(const Vec2& size);

		void SetPosition(const Vec2& position);

		void SetName(const std::string& name);

		Vec2 GetSize();

		Vec2 GetPosition();

		std::string GetName();

		std::string GetId();

		void Procedure(const Event& e);

		virtual void OnProcedure(const Event& e) {};

		ImGuiWindow();

		virtual ~ImGuiWindow() = default;

	protected:

		static void ImGuiStartCombo();

		static void ImGuiNextColumn();

		static void ImGuiEndCombo();

		static void ImGuiAlign(const std::string& text, float alignment);

		static bool ImGuiFile(const std::string& name, std::string& out);

		static bool ImGuiString(const std::string& name, std::string& out);

		static bool ImGuiInt(const std::string& name, int& value);

		static bool ImGuiBool(const std::string& name, bool& value);

		static bool ImGuiFloat(const std::string& name, float& value);

		static bool ImGuiDouble(const std::string& name, double& value);

		static bool ImGuiVec2(const std::string& name, VL::Vec2& value, float speed = 0.1f, float defaultValue = 0.0f);

		static bool ImGuiVec3(const std::string& name, VL::Vec3& value, float speed = 0.1f, float defaultValue = 0.0f);

		static bool ImGuiVec4(const std::string& name, VL::Vec4& value, float speed = 0.1f, float defaultValue = 0.0f);

		static void ImGuiColoredText(const std::string& text);

		static bool ImGuiListBegin(const std::string& name);

		static void ImGuiListEnd();

		static void ImGuiDragDropSource(const char* type, const std::string& payload);

		static std::string ImGuiDragDropTarget(const char* type);

		static VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize);

	private:

		std::string m_Name;

		std::string m_Id;

		bool m_IsWindowHovered;

		bool m_PositionChanged;

		bool m_SizeChanged;

		Vec2 m_Position;

		Vec2 m_Size;
	};
}

