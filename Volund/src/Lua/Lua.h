#pragma once

#include "Scene/Scene.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class Lua
	{
	public:

		static void Connect(sol::state& Lua);

	private:

		enum class LuaComponent
		{
			CAMERA = 1,
			CAMERA_MOVEMENT = 2,
			MESH_RENDERER = 3,
			POINT_LIGHT = 4,
			TAG = 5,
			TRANSFORM = 6
		};

		struct LuaEntity
		{
		public:

			void AddComponent(LuaComponent Component, const sol::table& Table);

			void DeleteComponent(LuaComponent Component, uint64_t I = 0);

			LuaEntity();

		private:

			Entity _Entity;
		};

		struct LuaMaterial
		{
		public:

			Ref<Material> Get();

			void SetInt(const std::string& Name, int32_t Value);

			void SetDouble(const std::string& Name, double Value);

			void SetVec2(const std::string& Name, Vec2 Value);

			void SetVec3(const std::string& Name, Vec3 Value);

			LuaMaterial(const std::string& ShaderPath);

		private:

			Ref<Material> _Material;
		};

		struct LuaMesh
		{
		public:

			Ref<Mesh> Get();

			LuaMesh(const std::string& MeshPath);

		private:

			Ref<Mesh> _Mesh;
		};

	};


}

