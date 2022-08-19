#pragma once

#include "Vec.h"

namespace Volund
{
	template<typename T>
	class Vec<3, T>
	{
	public:

		union { T X; T R; };
		union { T Y; T G; };
		union { T Z; T B; };

		Vec<3, T> operator+(T Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X += Other;
			NewVec.Y += Other;
			NewVec.Z += Other;

			return NewVec;
		}
		Vec<3, T> operator+(Vec<3, T> Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X += Other.X;
			NewVec.Y += Other.Y;
			NewVec.Z += Other.Z;

			return NewVec;
		}

		Vec<3, T> operator-(T Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X -= Other;
			NewVec.Y -= Other;
			NewVec.Z -= Other;

			return NewVec;
		}
		Vec<3, T> operator-(Vec<3, T> Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X -= Other.X;
			NewVec.Y -= Other.Y;
			NewVec.Z -= Other.Z;

			return NewVec;
		}

		Vec<3, T> operator*(T Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X *= Other;
			NewVec.Y *= Other;
			NewVec.Z *= Other;

			return NewVec;
		}
		Vec<3, T> operator*(Vec<3, T> Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X *= Other.X;
			NewVec.Y *= Other.Y;
			NewVec.Z *= Other.Z;

			return NewVec;
		}

		Vec<3, T> operator/(T Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X /= Other;
			NewVec.Y /= Other;
			NewVec.Z /= Other;

			return NewVec;
		}
		Vec<3, T> operator/(Vec<3, T> Other)
		{
			Vec<3, T> NewVec = (*this);

			NewVec.X /= Other.X;
			NewVec.Y /= Other.Y;
			NewVec.Z /= Other.Z;

			return NewVec;
		}

		void operator+=(T& Other)
		{
			this->X += Other;
			this->Y += Other;
			this->Z += Other;
		}
		void operator+=(Vec<3, T>& Other)
		{
			this->X += Other.X;
			this->Y += Other.Y;
			this->Z += Other.Z;
		}

		void operator-=(T& Other)
		{
			this->X -= Other;
			this->Y -= Other;
			this->Z -= Other;
		}
		void operator-=(Vec<3, T>& Other)
		{
			this->X -= Other.X;
			this->Y -= Other.Y;
			this->Z -= Other.Z;
		}

		void operator*=(T& Other)
		{
			this->X *= Other;
			this->Y *= Other;
			this->Z *= Other;
		}
		void operator*=(Vec<3, T>& Other)
		{
			this->X *= Other.X;
			this->Y *= Other.Y;
			this->Z *= Other.Z;
		}

		void operator/=(T& Other)
		{
			this->X /= Other;
			this->Y /= Other;
			this->Z /= Other;
		}
		void operator/=(Vec<3, T>& Other)
		{
			this->X /= Other.X;
			this->Y /= Other.Y;
			this->Z /= Other.Z;
		}

		void operator=(T& Other)
		{
			this->X = Other;
			this->Y = Other;
			this->Z = Other;
		}
		void operator=(Vec<3, T>& Other)
		{
			this->X = Other.X;
			this->Y = Other.Y;
			this->Z = Other.Z;
		}

		T& operator[](uint32_t i)
		{
			assert(i >= 0 && i < this->Length());

			switch (i)
			{
			case 0:
				return X;
			case 1:
				return Y;
			case 2:
				return Z;
			}

			return 0;
		}

		T const& operator[](uint32_t i) const
		{
			assert(i >= 0 && i < this->Length());

			switch (i)
			{
			case 0:
				return X;
			case 1:
				return Y;
			case 2:
				return Z;
			}

			return 0;
		}

		constexpr uint32_t Length() const
		{
			return 3;
		}

		Vec() = default;

		template<uint32_t L, typename T>
		Vec(Vec<L, T> Other)
		{
			(*this) = Other;
		}

		Vec(T X, T Y, T Z)
		{
			this->X = X;
			this->Y = Y;
			this->Z = Z;
		}

		Vec(T I)
		{
			this->X = I;
			this->Y = I;
			this->Z = I;
		}

	private:

	};

	typedef Vec<3, float> Vec3;
	typedef Vec<3, double> DVec3;
	typedef Vec<3, int32_t> IVec3;
	typedef Vec<3, int64_t> I64Vec3;

	typedef Vec<3, float> RGB;
}

