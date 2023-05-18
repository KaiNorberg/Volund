#pragma once

#include "Scene/Scene.h"

#include "../Serializer.h"

namespace Volund
{
	class SceneSerializer : public Serializer
	{
	public:

		SceneSerializer(Ref<Scene> scene);

	private:

		void SerializeEntity(Ref<Scene> scene, Entity entity);
	};
}