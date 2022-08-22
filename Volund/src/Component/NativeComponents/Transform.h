#pragma once

#include "Component/NativeComponent.h"

#include "Math/Math.h"

#define TRANSFORM_COMPONENT "Transform"

namespace Volund
{
	class Entity;

	class Transform : public NativeComponent
	{
	public:

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
		/// Returns a vector pointing forward.
		/// </summary>
		Vec3 GetFront();

		/// <summary>
		/// Returns a vector pointing right.
		/// </summary>
		Vec3 GetRight();

		/// <summary>
		/// Returns a vector pointing up.
		/// </summary>
		Vec3 GetUp();

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
		Quat Quaternion = Quat(Vec3(0.0f));

		void OnUpdate() override;

		const std::string Type() override;

		Transform() = default;

		Transform(Entity* Parent, JSON ComponentJSON);

	private:

		Entity* _Parent;

		Vec3 _Front = glm::vec3(0.0f);

		Vec3 _Right = glm::vec3(0.0f);

		Vec3 _Up = glm::vec3(0.0f);
	};
}

