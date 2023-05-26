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

		void SetSize(const Vec2& size);

		void SetPosition(const Vec2& position);

		Vec2 GetSize();

		Vec2 GetPosition();

		virtual const char* GetName() = 0;

		void Procedure(const Event& e);

		virtual void OnProcedure(const Event& e) {};

		virtual ~ImGuiWindow() = default;

	protected:

		template <typename T>
		void AddObject(Ref<T> object);

		template <typename T>
		Ref<T> GetObject(const std::string& objectId);

	private:

		Vec2 m_Position;

		Vec2 m_Size;

		PolyContainer<ImGuiObject> m_ImGuiObjects;
		std::vector<Ref<ImGuiObject>> m_ObjectDrawOrder;
	};

	template<typename T>
	inline void ImGuiWindow::AddObject(Ref<T> object)
	{
		this->m_ImGuiObjects.PushBack(object);
		this->m_ObjectDrawOrder.push_back(object);
	}

	template<typename T>
	inline Ref<T> ImGuiWindow::GetObject(const std::string& objectId)
	{
		
	}
}

