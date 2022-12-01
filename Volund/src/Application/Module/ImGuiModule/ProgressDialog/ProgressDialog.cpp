#include "PCH/PCH.h"
#include "ProgressDialog.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Volund
{
	void ProgressDialog::SetMessage(const std::string& Text)
	{
		_CatchMessage = Text;
	}

	void ProgressDialog::Start(std::function<void(void)> Catch, const std::string& Text)
	{
		_CatchMessage = Text;
		_CatchFuture = std::async(std::launch::async, Catch);

		_ShouldDraw = true;
	}

	bool ProgressDialog::Draw()
	{
		if (_ShouldDraw)
		{
			if (IsReady())
			{
				_ShouldDraw = false;
			}

			ImVec2 ScreenSize = ImGui::GetMainViewport()->Size;

			if (ImGui::Begin("Please wait...", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				ImVec2 WindowSize = ImVec2(250, 100);
				float SpinnerRadius = WindowSize.y / 4;

				ImGui::SetWindowSize(WindowSize);
				ImGui::SetWindowPos(ImVec2((ScreenSize.x - WindowSize.x) / 2, (ScreenSize.y - WindowSize.y) / 2));

				Spinner("###Spinner", SpinnerRadius, 5.0f, ImGui::GetColorU32(ImGuiCol_ButtonHovered));

				ImGui::SameLine();

				ImGui::SetCursorPosY(WindowSize.y / 2 - ImGui::GetTextLineHeight() / 2 + 4);

				ImGui::Text(_CatchMessage.c_str());
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
		return _CatchFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
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

		int num_segments = 30;
		int start = (int)abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (int i = 0; i < num_segments; i++) {
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
				centre.y + ImSin(a + g.Time * 8) * radius));
		}

		window->DrawList->PathStroke(color, false, thickness);

		return true;
	}

}
