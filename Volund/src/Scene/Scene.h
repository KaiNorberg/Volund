#pragma once

#include "Entity/Entity.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Mesh/Mesh.h"

#include "AssetLibrary/Asset/Assets.h"
#include "AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class Event;

	class Scene
	{
	public:

		 Ref<Entity> CreateEntity(std::string const& Name);

		 Ref<Entity> CreateEntity(std::string const& Name, Vec3 const& Position, Vec3 const& Rotation = Vec3(0.0f), Vec3 const& Scale = Vec3(1.0f));

		 bool DeleteEntity(std::string const& Name);

		 Ref<Entity> GetEntity(std::string const& Name);

		 bool HasEntity(std::string const& Name) const;

		 template<typename T>
		 std::vector<Ref<T>> const ComponentView();

		 void Update(TimeStep TS);

		 void EventCallback(Event* E);

		 virtual void OnEvent(Event* E);

		 virtual void OnUpdate(TimeStep TS);

		 static Ref<Scene> Deserialize(std::string const& FilePath);

		 void Serialize(std::string const& FilePath);

		 AssetLibrary Assets;

		 Scene();

		 virtual ~Scene() = default;

	private:

		std::vector<Ref<Entity>> _Entities;
	};

	template<typename T>
	inline std::vector<Ref<T>> const Scene::ComponentView()
	{
		std::vector<Ref<T>> ComponentView;
		for (auto const& Entity : _Entities)
		{
			if (Entity->HasComponent<T>())
			{
				auto const& View = Entity->ComponentView<T>();
				ComponentView.reserve(View.size());
				for (auto const& Component : View)
				{
					ComponentView.push_back(std::dynamic_pointer_cast<T>(Component));
				}
			}
		}

		return ComponentView;
	}
}

