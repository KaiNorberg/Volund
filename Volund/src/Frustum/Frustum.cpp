#include "PCH/PCH.h"
#include "Frustum.h"

namespace Volund
{
	Vec4& Frustum::operator[](int i)
	{
		return this->_Planes[i];
	}

	bool Frustum::IsAABBInside(const Vec3 minp, const Vec3 maxp) const
	{
		// check box outside/inside of frustum
		for (int i = 0; i < (int)Plane::Count; i++)
		{
			if ((glm::dot(_Planes[i], glm::vec4(minp.x, minp.y, minp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(maxp.x, minp.y, minp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(minp.x, maxp.y, minp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(maxp.x, maxp.y, minp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(minp.x, minp.y, maxp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(maxp.x, minp.y, maxp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(minp.x, maxp.y, maxp.z, 1.0f)) < 0.0) &&
				(glm::dot(_Planes[i], glm::vec4(maxp.x, maxp.y, maxp.z, 1.0f)) < 0.0))
			{
				return false;
			}
		}

		// check frustum outside/inside box
		int out;
		out = 0; for (int i = 0; i < 8; i++) out += ((_Points[i].x > maxp.x) ? 1 : 0); if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((_Points[i].x < minp.x) ? 1 : 0); if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((_Points[i].y > maxp.y) ? 1 : 0); if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((_Points[i].y < minp.y) ? 1 : 0); if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((_Points[i].z > maxp.z) ? 1 : 0); if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((_Points[i].z < minp.z) ? 1 : 0); if (out == 8) return false;

		return true;
	}

	Frustum::Frustum(Mat4x4 ViewProjMatrix)
	{
		ViewProjMatrix = glm::transpose(ViewProjMatrix);
		_Planes[(int)Plane::Left] = ViewProjMatrix[3] + ViewProjMatrix[0];
		_Planes[(int)Plane::Right] = ViewProjMatrix[3] - ViewProjMatrix[0];
		_Planes[(int)Plane::Bottom] = ViewProjMatrix[3] + ViewProjMatrix[1];
		_Planes[(int)Plane::Top] = ViewProjMatrix[3] - ViewProjMatrix[1];
		_Planes[(int)Plane::Near] = ViewProjMatrix[3] + ViewProjMatrix[2];
		_Planes[(int)Plane::Far] = ViewProjMatrix[3] - ViewProjMatrix[2];

		glm::vec3 Crosses[(int)Plane::Combinations] = {
			glm::cross(glm::vec3(_Planes[(int)Plane::Left]),   glm::vec3(_Planes[(int)Plane::Right])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Left]),   glm::vec3(_Planes[(int)Plane::Bottom])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Left]),   glm::vec3(_Planes[(int)Plane::Top])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Left]),   glm::vec3(_Planes[(int)Plane::Near])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Left]),   glm::vec3(_Planes[(int)Plane::Far])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Right]),  glm::vec3(_Planes[(int)Plane::Bottom])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Right]),  glm::vec3(_Planes[(int)Plane::Top])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Right]),  glm::vec3(_Planes[(int)Plane::Near])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Right]),  glm::vec3(_Planes[(int)Plane::Far])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Bottom]), glm::vec3(_Planes[(int)Plane::Top])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Bottom]), glm::vec3(_Planes[(int)Plane::Near])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Bottom]), glm::vec3(_Planes[(int)Plane::Far])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Top]),    glm::vec3(_Planes[(int)Plane::Near])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Top]),    glm::vec3(_Planes[(int)Plane::Far])),
			glm::cross(glm::vec3(_Planes[(int)Plane::Near]),   glm::vec3(_Planes[(int)Plane::Far]))
		};

		_Points[0] = Intersection<Plane::Left, Plane::Bottom, Plane::Near>(Crosses);
		_Points[1] = Intersection<Plane::Left, Plane::Top, Plane::Near>(Crosses);
		_Points[2] = Intersection<Plane::Right, Plane::Bottom, Plane::Near>(Crosses);
		_Points[3] = Intersection<Plane::Right, Plane::Top, Plane::Near>(Crosses);
		_Points[4] = Intersection<Plane::Left, Plane::Bottom, Plane::Far>(Crosses);
		_Points[5] = Intersection<Plane::Left, Plane::Top, Plane::Far>(Crosses);
		_Points[6] = Intersection<Plane::Right, Plane::Bottom, Plane::Far>(Crosses);
		_Points[7] = Intersection<Plane::Right, Plane::Top, Plane::Far>(Crosses);
	}
}