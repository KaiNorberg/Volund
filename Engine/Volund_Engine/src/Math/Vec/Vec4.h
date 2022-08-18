#pragma once

#include "Vec.h"

namespace Volund
{
	template<typename T>
	class Vec<4, T>
	{
	public:

		union { T X; T R; };
		union { T Y; T G; };
		union { T Z; T B; };
		union { T W; T A; };

		Vec<4, T> operator+(T Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X += Other;
			NewVec.Y += Other;
			NewVec.Z += Other;
			NewVec.W += Other;

			return NewVec;
		}
		Vec<4, T> operator+(Vec<4, T> Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X += Other.X;
			NewVec.Y += Other.Y;
			NewVec.Z += Other.Z;
			NewVec.W += Other.W;

			return NewVec;
		}

		Vec<4, T> operator-(T Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X -= Other;
			NewVec.Y -= Other;
			NewVec.Z -= Other;
			NewVec.W -= Other;

			return NewVec;
		}
		Vec<4, T> operator-(Vec<4, T> Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X -= Other.X;
			NewVec.Y -= Other.Y;
			NewVec.Z -= Other.Z;
			NewVec.W -= Other.W;

			return NewVec;
		}

		Vec<4, T> operator*(T Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X *= Other;
			NewVec.Y *= Other;
			NewVec.Z *= Other;
			NewVec.W *= Other;

			return NewVec;
		}
		Vec<4, T> operator*(Vec<4, T> Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X *= Other.X;
			NewVec.Y *= Other.Y;
			NewVec.Z *= Other.Z;
			NewVec.W *= Other.W;

			return NewVec;
		}

		Vec<4, T> operator/(T Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X /= Other;
			NewVec.Y /= Other;
			NewVec.Z /= Other;
			NewVec.W /= Other;

			return NewVec;
		}
		Vec<4, T> operator/(Vec<4, T> Other)
		{
			Vec<4, T> NewVec = (*this);

			NewVec.X /= Other.X;
			NewVec.Y /= Other.Y;
			NewVec.Z /= Other.Z;
			NewVec.W /= Other.W;

			return NewVec;
		}

		void operator+=(T& Other)
		{
			this->X += Other;
			this->Y += Other;
			this->Z += Other;			
			this->W += Other;
		}
		void operator+=(Vec<4, T>& Other)
		{
			this->X += Other.X;
			this->Y += Other.Y;
			this->Z += Other.Z;			
			this->W += Other.W;
		}

		void operator-=(T& Other)
		{
			this->X -= Other;
			this->Y -= Other;
			this->Z -= Other;
			this->W -= Other;
		}
		void operator-=(Vec<4, T>& Other)
		{
			this->X -= Other.X;
			this->Y -= Other.Y;
			this->Z -= Other.Z;
			this->W -= Other.W;
		}

		void operator*=(T& Other)
		{
			this->X *= Other;
			this->Y *= Other;
			this->Z *= Other;
			this->W *= Other;
		}
		void operator*=(Vec<4, T>& Other)
		{
			this->X *= Other.X;
			this->Y *= Other.Y;
			this->Z *= Other.Z;
			this->W *= Other.W;
		}

		void operator/=(T& Other)
		{
			this->X /= Other;
			this->Y /= Other;
			this->Z /= Other;
			this->W /= Other;
		}
		void operator/=(Vec<4, T>& Other)
		{
			this->X /= Other.X;
			this->Y /= Other.Y;
			this->Z /= Other.Z;
			this->W /= Other.W;
		}

		void operator=(T& Other)
		{
			this->X = Other;
			this->Y = Other;
			this->Z = Other;
			this->W = Other;
		}
		void operator=(Vec<4, T>& Other)
		{
			this->X = Other.X;
			this->Y = Other.Y;
			this->Z = Other.Z;
			this->W = Other.W;
		}

		T operator[](uint32_t i) const
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
			case 3:
				return W;
			}
		}

		constexpr uint32_t Length() const
		{
			return 4;
		}

		Vec() = default;

		template<uint32_t L, typename T>
		Vec(Vec<L, T> Other)
		{
			(*this) = Other;
		}

		Vec(T X, T Y, T Z, T W)
		{
			this->X = X;
			this->Y = Y;
			this->Z = Z;			
			this->W = W;
		}

		Vec(T I)
		{
			this->X = I;
			this->Y = I;
			this->Z = I;
			this->W = I;
		}

	private:

	};

	typedef Vec<4, float> Vec4;
	typedef Vec<4, double> DVec4;
	typedef Vec<4, int32_t> IVec4;
	typedef Vec<4, int64_t> I64Vec4;

	typedef Vec<4, float> RGBA;
}

