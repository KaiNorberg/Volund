#pragma once

#include "Component/NativeComponent.h"

namespace Volund
{
	class Entity;

	class Transform3D : public NativeComponent
	{
	public:
		/*
		/// <summary>
		/// Sets the rotation of the entity.
		/// </summary>
		void SetRotation(Vec3 const& Rotation);

		/// <summary>
		/// Returns the rotation of the entity.
		/// </summary>
		Vec3 GetRotation() const;

		/// <summary>
		/// Adds the rotation given to the entity rotation.
		/// </summary>
		void AddRotation(Vec3 const& Rotation);

		/// <summary>
		/// The vector pointing forward, (Read only)
		/// </summary>
		const Vec3& Front = Front_P;

		/// <summary>
		/// The vector pointing right, (Read only)
		/// </summary>
		const Vec3& Right = Right_P;

		/// <summary>
		/// The vector pointing up, (Read only)
		/// </summary>
		const Vec3& Up = Up_P;

		/// <summary>
		/// The position of the entity.
		/// </summary>
		Vec3 Position = Vec3(0.0f);

		/// <summary>
		/// The scale of the entity.
		/// </summary>
		Vec3 Scale = Vec3(1.0f);

		/// <summary>
		/// The quaternion representing the rotation of the entity.
		/// </summary>
		Quat Quaternion = Quat(Vec3(0.0f));*/

		const std::string Name() override;

		Transform3D() = default;

		Transform3D(Entity* Parent, JSON ComponentJSON);

	private:

		/*Vec3 Front_P = glm::vec3(0.0f);

		Vec3 Right_P = glm::vec3(0.0f);

		Vec3 Up_P = glm::vec3(0.0f);*/

		Entity* Parent;
	};
}

