#include "PCH/PCH.h"
#include "ProgressDialog.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Volund
{
	void ProgressDialog::SetMessage(const std::string& text)
	{
		m_CatchMessage = text;
	}

	void ProgressDialog::Start(std::function<void(void)> Catch, const std::string& text)
	{
		m_CatchMessage = text;
		m_CatchFuture = std::async(std::launch::async, Catch);

		m_ShouldDraw = true;
	}

	bool ProgressDialog::Draw()
	{
		if (m_ShouldDraw)
		{
			if (IsReady())
			{
				m_ShouldDraw = false;
			}

			const ImVec2 screenSize = ImGui::GetMainViewport()->Size;

			if (ImGui::Begin("Please wait...", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				const ImVec2 windowSize = ImVec2(250, 100);
				const float spinnerRadius = windowSize.y / 4;

				ImGui::SetWindowSize(windowSize);
				ImGui::SetWindowPos(ImVec2((screenSize.x - windowSize.x) / 2, (screenSize.y - windowSize.y) / 2));

				Spinner("###Spinner", spinnerRadius, 5.0f, ImGui::GetColorU32(ImGuiCol_ButtonHovered));

				ImGui::SameLine();

				ImGui::SetCursorPosY(windowSize.y / 2 - ImGui::GetTextLineHeight() / 2 + 4);

				ImGui::Text(m_CatchMessage.c_str());
			}

			ImGui::End();

			return true;
		}
		else
		{
			return false;
		}
	}

	bool ProgressDialog::IsReady()
	{
		return m_CatchFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
	}

	/// <summary>
	/// Written by zfedoran https://github.com/ocornut/imgui/issues/1901
	/// </summary>
	bool ProgressDialog::Spinner(const char* label, float radius, int thickness, const uint32_t& color)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		// Render
		window->DrawList->PathClear();

		int numSegments = 30;
		int start = (int)abs(ImSin(g.Time * 1.8f) * (numSegments - 5));

		const float aMin = IM_PI * 2.0f * ((float)start) / (float)numSegments;
		const float aMax = IM_PI * 2.0f * ((float)numSegments - 3) / (float)numSegments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (int i = 0; i < numSegments; i++) {
			const float a = aMin + ((float)i / (float)numSegments) * (aMax - aMin);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
				centre.y + ImSin(a + g.Time * 8) * radius));
		}

		window->DrawList->PathStroke(color, false, thickness);

		return true;
	}

}
