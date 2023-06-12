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

		template <typename T>
		void PushObject(T* object);

		template <typename T>
		void PushObject(Ref<T> object);

		template <typename T>
		Ref<T> GetObject(const std::string& objectId);

	private:

		std::string m_Name;

		std::string m_Id;

		bool m_PositionChanged;

		bool m_SizeChanged;

		Vec2 m_Position;

		Vec2 m_Size;

		PolyContainer<ImGuiObject> m_ImGuiObjects;
		std::vector<Ref<ImGuiObject>> m_ObjectDrawOrder;
	};

	template<typename T>
	inline void ImGuiWindow::PushObject(T* object)
	{
		this->PushObject(Ref<T>(object));
	}

	template<typename T>
	inline void ImGuiWindow::PushObject(Ref<T> object)
	{
		this->m_ImGuiObjects.PushBack(object);
		this->m_ObjectDrawOrder.push_back(object);
	}

	template<typename T>
	inline Ref<T> ImGuiWindow::GetObject(const std::string& objectId)
	{
		for (int i = 0; i < this->m_ImGuiObjects.Size<T>(); i++)
		{
			auto object = this->m_ImGuiObjects.Get<T>(i);
			if (object->GetID() == objectId)
			{
				return object;
			}
		}

		return nullptr;
	}
}

