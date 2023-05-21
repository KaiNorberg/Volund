#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class ImGuiObject
	{
	public:

		std::string GetID();

		virtual void Procedure(const Event& e) = 0;

		virtual ~ImGuiObject() = default;

	protected:

		std::string m_Id;
	};
}