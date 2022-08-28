#pragma once

#include "Component/Component.h"

namespace Volund
{
	class Transform : public Component
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

		void OnUpdate(TimeStep TS) override;

		Transform(Vec3 const& Position = Vec3(0.0f), Vec3 const& Scale = Vec3(0.0f));

	private:

		Vec3 _Front = glm::vec3(0.0f);

		Vec3 _Right = glm::vec3(0.0f);

		Vec3 _Up = glm::vec3(0.0f);
	};
}

