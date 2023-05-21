#pragma once

#include "EventDispatcher/Event.h"
#include "PolyContainer/PolyContainer.h"
#include "ImGuiObject/ImGuiObject.h"

namespace Volund
{
	class ImGuiWindow
	{
	public:

		bool IsActive = true;

		Vec2 Position;

		Vec2 Size;

		virtual const char* GetName() = 0;

		void Procedure(const Event& e);

		virtual ~ImGuiWindow() = default;

	protected:

		template <typename T>
		void AddObject(Ref<T> object);

	private:

		Vec2 m_PreviousPosition;

		Vec2 m_PreviousSize;

		PolyContainer<ImGuiObject> m_ImGuiObjects;
		std::vector<Ref<ImGuiObject>> m_ObjectDrawOrder;
	};

	template<typename T>
	inline void ImGuiWindow::AddObject(Ref<T> object)
	{
		this->m_ImGuiObjects.PushBack(object);
		this->m_ObjectDrawOrder.push_back(object);
	}
}

