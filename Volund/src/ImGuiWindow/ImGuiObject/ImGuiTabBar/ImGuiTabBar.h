#pragma once

#include "../ImGuiObject.h"
#include "PolyContainer/PolyContainer.h"

namespace Volund
{	
	class ImGuiTabBar : public ImGuiObject
	{
	public:

		template <typename T>
		void PushObject(const std::string name, Ref<T> object);

		template <typename T>
		Ref<T> GetObject(const std::string& objectId);

		void Procedure(const Event& e) override;

	private:

		struct Tab
		{
			std::string Name;
			Ref<ImGuiObject> Object;
		};

		std::vector<Tab> m_Tabs;
	};

	template<typename T>
	inline void ImGuiTabBar::PushObject(const std::string name, Ref<T> object)
	{
		this->m_Tabs.push_back({name, object});
	}

	/*template<typename T>
	inline Ref<T> ImGuiTabBar::GetObject(const std::string& objectId)
	{
		for (int i = 0; i < this->m_Tabs.Size<T>(); i++)
		{
			auto object = this->m_Tabs.Get<T>(i);
			if (object->GetID() == objectId)
			{
				return object;
			}
		}

		return nullptr;
	}*/
}

