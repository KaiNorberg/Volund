#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class ImGuiObject
	{
	public:

		bool IsActive = true;

		std::string GetId();

		void SetDragDropTargetCallback(std::function<void(void)> callback);
		std::function<void(void)> GetDragDropTargetCallback();

		void SetDragDropSourceCallback(std::function<void(void)> callback);
		std::function<void(void)> GetDragDropSourceCallback();

		virtual void Procedure(const Event& e) = 0;

		ImGuiObject();

		virtual ~ImGuiObject() = default;

	protected:

		static void ImGuiColoredText(const std::string& text);

	private:

		std::function<void(void)> m_DragDropTargetCallback = nullptr;

		std::function<void(void)> m_DragDropSourceCallback = nullptr;

		std::string m_Id;
	};
}