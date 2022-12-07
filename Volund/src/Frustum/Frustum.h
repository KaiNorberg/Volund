#pragma once

namespace Volund
{
    class Frustum
    {
    public:

		enum class Plane
		{
			Left = 0,
			Right,
			Bottom,
			Top,
			Near,
			Far,
			Count,
			Combinations = Count * (Count - 1) / 2
		};

		Vec4& operator[](int i);

		bool IsAABBInside(const Vec3 minp, const Vec3 maxp) const;

        Frustum(Mat4x4 ViewProjMatrix);

    private:

		template<Plane i, Plane j>
		struct ij2k
		{
			enum { k = (int)i * (9 - (int)i) / 2 + (int)j - 1 };
		};

		template<Plane a, Plane b, Plane c>
		Vec3 Intersection(const Vec3* crosses) const;

		Vec4 _Planes[(int)Plane::Count] = {};
		Vec3 _Points[8] = {};
    }; 
	
	template<Frustum::Plane a, Frustum::Plane b, Frustum::Plane c>
	inline Vec3 Frustum::Intersection(const Vec3* crosses) const
	{
		float D = glm::dot(glm::vec3(_Planes[(int)a]), crosses[ij2k<b, c>::k]);
		glm::vec3 res = glm::mat3(crosses[ij2k<b, c>::k], -crosses[ij2k<a, c>::k], crosses[ij2k<a, b>::k]) *
			glm::vec3(_Planes[(int)a].w, _Planes[(int)b].w, _Planes[(int)c].w);
		return res * (-1.0f / D);
	}
}
