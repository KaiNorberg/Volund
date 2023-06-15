#pragma once

#include "EventDispatcher/Event.h"
#include "PolyContainer/PolyContainer.h"

#define VOLUND_IMGUI_FILE "VOLUND_IMGUI_FILE"
#define VOLUND_IMGUI_DIRECTORY "VOLUND_IMGUI_DIRECTORY"

namespace Volund
{
	class ImGuiWindow
	{
	public:

		bool IsActive = true;

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

		static void ImGuiString(const std::string& name, std::string& out);

		static void ImGuiBool(const std::string& name, bool& value);

		static void ImGuiFloat(const std::string& name, float& value);

		static void ImGuiVec3(std::string_view Name, VL::Vec3* Value, float Speed = 0.1f, float DefaultValue = 0.0f);

		static void ImGuiColoredText(const std::string& text);

		static void ImGuiTextList(const std::string& name, const std::vector<std::string>& textList);

		static VL::Vec2 ToScreenSpace(const VL::Mat4x4& ViewProjMatrix, const VL::Vec3& Position, const VL::Vec2& WindowPos, const VL::Vec2& WindowSize);

	private:

		std::string m_Name;

		std::string m_Id;

		bool m_PositionChanged;

		bool m_SizeChanged;

		Vec2 m_Position;

		Vec2 m_Size;
	};
}

