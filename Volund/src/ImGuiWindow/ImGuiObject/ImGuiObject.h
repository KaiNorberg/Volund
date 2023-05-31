#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class ImGuiObject
	{
	public:

		bool IsActive = true;

		std::string GetId();

		virtual void Procedure(const Event& e) = 0;

		ImGuiObject();

		virtual ~ImGuiObject() = default;

	protected:

		static void ImGuiColoredText(const std::string& text);

	private:

		std::string m_Id;
	};
}