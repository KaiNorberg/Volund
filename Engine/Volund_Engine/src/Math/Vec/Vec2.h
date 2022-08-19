#pragma once

#include "Vec.h"

namespace Volund
{
	template<typename T>
	class Vec<2, T>
	{
	public:

		union { T X; T R; };
		union { T Y; T G; };

		Vec<2, T> operator+(T Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X += Other;
			NewVec.Y += Other;

			return NewVec;
		}
		Vec<2, T> operator+(Vec<2, T> Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X += Other.X;
			NewVec.Y += Other.Y;

			return NewVec;
		}

		Vec<2, T> operator-(T Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X -= Other;
			NewVec.Y -= Other;

			return NewVec;
		}
		Vec<2, T> operator-(Vec<2, T> Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X -= Other.X;
			NewVec.Y -= Other.Y;

			return NewVec;
		}

		Vec<2, T> operator*(T Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X *= Other;
			NewVec.Y *= Other;

			return NewVec;
		}
		Vec<2, T> operator*(Vec<2, T> Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X *= Other.X;
			NewVec.Y *= Other.Y;

			return NewVec;
		}

		Vec<2, T> operator/(T Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X /= Other;
			NewVec.Y /= Other;

			return NewVec;
		}
		Vec<2, T> operator/(Vec<2, T> Other)
		{
			Vec<2, T> NewVec = (*this);

			NewVec.X /= Other.X;
			NewVec.Y /= Other.Y;

			return NewVec;
		}

		void operator+=(T& Other)
		{
			this->X += Other;
			this->Y += Other;
		}
		void operator+=(Vec<2, T>& Other)
		{
			this->X += Other.X;
			this->Y += Other.Y;
		}

		void operator-=(T& Other)
		{
			this->X -= Other;
			this->Y -= Other;
		}
		void operator-=(Vec<2, T>& Other)
		{
			this->X -= Other.X;
			this->Y -= Other.Y;
		}

		void operator*=(T& Other)
		{
			this->X *= Other;
			this->Y *= Other;
		}
		void operator*=(Vec<2, T>& Other)
		{
			this->X *= Other.X;
			this->Y *= Other.Y;
		}

		void operator/=(T& Other)
		{
			this->X /= Other;
			this->Y /= Other;
		}
		void operator/=(Vec<2, T>& Other)
		{
			this->X /= Other.X;
			this->Y /= Other.Y;
		}

		void operator=(T& Other)
		{
			this->X = Other;
			this->Y = Other;
		}
		void operator=(Vec<2, T>& Other)
		{
			this->X = Other.X;
			this->Y = Other.Y;
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
			}

			return 0;
		}

		constexpr uint32_t Length() const
		{
			return 2;
		}

		Vec() = default;

		template<uint32_t L, typename T>
		Vec(Vec<L, T> Other)
		{
			(*this) = Other;
		}

		Vec(T X, T Y)
		{
			this->X = X;
			this->Y = Y;
		}

		Vec(T I)
		{
			this->X = I;
			this->Z = I;
		}

	private:

	};

	typedef Vec<2, float> Vec2;
	typedef Vec<2, double> DVec2;
	typedef Vec<2, int32_t> IVec2;
	typedef Vec<2, int64_t> I64Vec2;
}

