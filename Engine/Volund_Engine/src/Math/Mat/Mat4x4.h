#pragma once

#include "Mat.h"
#include "Math/Vec/Vec.h"

namespace Volund
{
	template<typename T>
	struct Mat<4, 4, T>
	{
	public:

		void operator*=(T S)
		{
			this->Matrix[0] *= S;
			this->Matrix[1] *= S;
			this->Matrix[2] *= S;
			this->Matrix[3] *= S;
		}

		void operator*=(Mat<4, 4, T> const& M)
		{
			(*this) = *this * M;
		}

		void operator/=(T S)
		{
			this->Matrix[0] /= S;
			this->Matrix[1] /= S;
			this->Matrix[2] /= S;
			this->Matrix[3] /= S;
		}

		Mat<4, 4, T> operator*(Mat<4, 4, T> const& M) const
		{
			Vec<4, T> const SrcA0 = (*this)[0];
			Vec<4, T> const SrcA1 = (*this)[1];
			Vec<4, T> const SrcA2 = (*this)[2];
			Vec<4, T> const SrcA3 = (*this)[3];

			Vec<4, T> const SrcB0 = M[0];
			Vec<4, T> const SrcB1 = M[1];
			Vec<4, T> const SrcB2 = M[2];
			Vec<4, T> const SrcB3 = M[3];

			Mat<4, 4, T> Result;
			Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
			Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
			Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
			Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
			return Result;
		}

		T& operator[](uint32_t i)
		{
			assert(i >= 0 && i < this->Length());

			return Matrix[i];
		}

		T const& operator[](uint32_t i) const
		{
			assert(i >= 0 && i < this->Length());

			return Matrix[i];
		}

		Mat() = default;

		Mat(Mat<4, 4, T> const& M)
		{
			(*this) = M;
		}

		Mat(T const& X)
		{
			Matrix[0] = X;
			Matrix[1] = X;
			Matrix[2] = X;
			Matrix[3] = X;
		}

	private:

		Vec<4, T> Matrix[4];
	};

	typedef Mat<4, 4, float> Mat4x4;
}