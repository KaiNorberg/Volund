#pragma once

#include "Entity/Entity.h"

#include "AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class Event;

	class Scene
	{
	public:
		Ref<Entity> CreateEntity(const std::string& Name);

		Ref<Entity> CreateEntity(const std::string& Name, const Vec3& Position, const Vec3& Rotation = Vec3(0.0f),
		                         const Vec3& Scale = Vec3(1.0f));

		bool DeleteEntity(const std::string& Name);

		Ref<Entity> GetEntity(const std::string& Name);

		bool HasEntity(const std::string& Name) const;

		template <typename T>
		const std::vector<Ref<T>> ComponentView();

		void Update(TimeStep TS);

		void EventCallback(Event* E);

		virtual void OnEvent(Event* E);

		virtual void OnUpdate(TimeStep TS);

		static Ref<Scene> Deserialize(const std::string& FilePath);

		void Serialize(const std::string& FilePath);

		AssetLibrary Assets;

		Scene();

		virtual ~Scene() = default;

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
