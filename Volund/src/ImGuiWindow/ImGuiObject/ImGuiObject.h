#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class ImGuiWindow;

	class ImGuiObject
	{
	public:

		bool IsActive = true;

		std::string GetID();

		virtual void Procedure(const Event& e) = 0;

		virtual ~ImGuiObject() = default;

	protected:

		static void ImGuiColoredText(const std::string& text);

		std::string m_Id;
	};
}