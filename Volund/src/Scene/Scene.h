#pragma once

#include "Entity/Entity.h"

namespace Volund
{
	class Event;

	class Scene
	{
	public:
		Ref<Entity> CreateEntity(std::string_view Name);

		Ref<Entity> CreateEntity(std::string_view Name, const Vec3& Position, const Vec3& Rotation = Vec3(0.0f), const Vec3& Scale = Vec3(1.0f));

		bool DeleteEntity(std::string_view Name);

		Ref<Entity> GetEntity(std::string_view Name);

		bool HasEntity(std::string_view Name) const;

		template <typename T>
		const std::vector<Ref<T>> ComponentView();

		virtual void OnEvent(Event*);

		virtual void OnUpdate(TimeStep);

		static Ref<Scene> Deserialize(std::string_view FilePath);

		void Serialize(std::string_view FilePath);

		std::vector<Ref<Entity>>::iterator begin();
		std::vector<Ref<Entity>>::iterator end();

		std::vector<Ref<Entity>>::const_iterator begin() const;
		std::vector<Ref<Entity>>::const_iterator end() const;

		Scene();

	private:
		std::vector<Ref<Entity>> _Entities;
	};

	template <typename T>
	const std::vector<Ref<T>> Scene::ComponentView()
	{
		std::vector<Ref<T>> ComponentView;
		for (const auto& Entity : _Entities)
		{
			if (Entity->HasComponent<T>())
			{
				const auto& View = Entity->ComponentView<T>();
				ComponentView.reserve(View.size());
				for (const auto& Component : View)
				{
					ComponentView.push_back(std::dynamic_pointer_cast<T>(Component));
				}
			}
		}

		return ComponentView;
	}
}
