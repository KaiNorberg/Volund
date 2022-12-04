#pragma once

#include "Scene/Scene.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	class Lua
	{
	public:

		static void Connect(sol::state& Lua);

		enum class LuaComponent
		{
			CAMERA = 1,
			CAMERA_MOVEMENT = 2,
			MESH_RENDERER = 3,
			POINT_LIGHT = 4,
			SCRIPT = 5,
			TAG = 6,
			TRANSFORM = 7,
		};

		static sol::object LuaRequire(sol::this_state S, std::string Filepath);

		static void LuaPrint(std::string String);

		struct LuaInput
		{
		public:

			bool IsHeld(char KeyCode) const;
			bool IsPressed(char KeyCode);

			bool IsMouseButtonHeld(char Button) const;
			bool IsMouseButtonPressed(char Button);

			uint32_t GetScrollPosition() const;

			Vec2 GetMousePosition() const;

		};

		struct LuaEntity
		{
		public:

			void AddComponent(LuaComponent Component, const sol::table& Table);

			void DeleteComponent(LuaComponent Component, uint64_t I = 0);

			sol::object GetComponent(sol::this_state S, LuaComponent Component, uint64_t I = 0);

			LuaEntity(Entity Entity);

			LuaEntity();

		private:

			Entity _Entity;
		};

		struct LuaMaterial
		{
		public:

			Ref<Material> Get();

			void SetInt(const std::string& Name, lua_Integer Value);

			void SetFloat(const std::string& Name, float Value);

			void SetDouble(const std::string& Name, double Value);

			void SetVec2(const std::string& Name, Vec2 Value);

			void SetVec3(const std::string& Name, Vec3 Value);

			LuaMaterial(Ref<Material> Material);

			LuaMaterial(const std::string& ShaderPath);

		private:

			Ref<Material> _Material;
		};

		struct LuaMesh
		{
		public:

			Ref<Mesh> Get();

			LuaMesh(Ref<Mesh> Mesh);

			LuaMesh(const std::string& MeshPath);

		private:

			Ref<Mesh> _Mesh;
		};

		struct LuaCamera
		{
		public:

			float GetFOV();
			void SetFOV(float FOV);

			float GetNearPlane();
			void SetNearPlane(float NearPlane);

			float GetFarPlane();
			void SetFarPlane(float FarPlane);

			bool IsActive();
			void SetActive();

			LuaCamera(Ref<Camera> Camera);

		private:

			Ref<Camera> _Camera;
		};

		struct LuaCameraMovement
		{
		public:

			float GetSpeed();
			void SetSpeed(float Speed);

			float GetSensitivity();
			void SetSensitivity(float Sensitivity);

			LuaCameraMovement(Ref<CameraMovement> CameraMovement);

		private:

			Ref<CameraMovement> _CameraMovement;
		};

		struct LuaMeshRenderer
		{
		public:

			void SetMesh(LuaMesh NewMesh);
			void SetMaterial(LuaMaterial NewMaterial);

			LuaMesh GetMesh();
			LuaMaterial GetMaterial();

			LuaMeshRenderer(Ref<MeshRenderer> MeshRenderer);

		private:

			Ref<MeshRenderer> _MeshRenderer;
		};

		struct LuaPointLight
		{
		public:

			Vec3 GetColor();
			void SetColor(Vec3 Color);

			void SetBrightness(float Brightness);
			float GetBrightness();

			LuaPointLight(Ref<PointLight> PointLight);

		private:

			Ref<PointLight> _PointLight;
		};

		struct LuaScript
		{
		public:

			LuaScript(Ref<Script> Script);

		private:

			Ref<Script> _Script;
		};

		struct LuaTag
		{
		public:

			std::string Get();
			void Set(std::string String);

			LuaTag(Ref<Tag> Tag);

		private:

			Ref<Tag> _Tag;
		};

		struct LuaTransform
		{
		public:

			void SetPosition(const Vec3& Position);
			Vec3 GetPosition() const;
			void AddPosition(const Vec3& Position);

			void SetRotation(const Vec3& Rotation);
			Vec3 GetRotation() const;
			void AddRotation(const Vec3& Rotation);

			void SetScale(const Vec3& Scale);
			Vec3 GetScale() const;
			void AddScale(const Vec3& Scale);

			Vec3 GetFront() const;
			Vec3 GetRight() const;
			Vec3 GetUp() const;

			LuaTransform(Ref<Transform> Transform);

		private:

			Ref<Transform> _Transform;
		};
	};


}

