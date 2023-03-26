#pragma once

namespace Volund
{
	template<int Size, typename T>
	class LuaVec
	{
	public:

		T x = 0;

		T y = 0;

		T z = 0;

		T w = 0;

		LuaVec<Size, T> Cross(const LuaVec<Size, T>& other);

		LuaVec<Size, T> Normalize();

		LuaVec<Size, T> Reflect(const LuaVec<Size, T>& normal);

		T Length();

		T Length2();

		int GetSize();
			
		glm::vec<Size, T> GLM() const;

		operator glm::vec<Size, T>() const;

		template<int otherSize, typename otherT>
		operator LuaVec<otherSize, otherT>() const;

		T& operator[](int index);
		const T& operator[](int index) const;

		LuaVec<Size, T> operator+(const LuaVec<Size, T>& other);
		LuaVec<Size, T> operator+(T other);

		LuaVec<Size, T> operator-(const LuaVec<Size, T>& other);
		LuaVec<Size, T> operator-(T other);

		LuaVec<Size, T> operator*(const LuaVec<Size, T>& other);
		LuaVec<Size, T> operator*(T other);

		LuaVec<Size, T> operator/(const LuaVec<Size, T>& other);
		LuaVec<Size, T> operator/(T other);

		void operator+=(const LuaVec<Size, T>& other);
		void operator+=(T other);

		void operator-=(const LuaVec<Size, T>& other);
		void operator-=(T other);

		void operator*=(const LuaVec<Size, T>& other);
		void operator*=(T other);

		void operator/=(const LuaVec<Size, T>& other);
		void operator/=(T other);

		void operator=(const LuaVec<Size, T>& other);
		void operator=(T other);

		LuaVec() = default;

		LuaVec(const LuaVec<Size, T>& vector);
		LuaVec(const glm::vec<Size, T>& vector);

		LuaVec(T scalar31, T scalar32, T scalar33, T scalar34);
		LuaVec(T scalar31, T scalar32, T scalar33);
		LuaVec(T scalar31, T scalar32);
		LuaVec(T scalar3);

	private:
	};

	template<>
	inline LuaVec<3, float> LuaVec<3, float>::Cross(const LuaVec<3, float>& other)
	{
		return LuaVec<3, float>(glm::cross(this->GLM(), other.GLM()));
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::Cross(const LuaVec<Size, T>& other)
	{
		return LuaVec<Size, T>(0.0);
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::Normalize()
	{
		T length = this->Length();
		LuaVec<Size, T> temp;
		for (int i = 0; i < Size; i++)
		{
			temp[i] = (*this)[i] / length;
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::Reflect(const LuaVec<Size, T>& normal)
	{
		return LuaVec<Size, T>(glm::reflect(this->GLM(), normal.GLM()));
	}

	template<int Size, typename T>
	inline T LuaVec<Size, T>::Length()
	{
		return sqrt(this->Length2());
	}

	template<int Size, typename T>
	inline T LuaVec<Size, T>::Length2()
	{
		T length = T(0);
		for (int i = 0; i < Size; i++)
		{
			length += ((*this)[i] * (*this)[i]);
		}

		return length;
	}

	template<int Size, typename T>
	inline int LuaVec<Size, T>::GetSize() 
	{
		return Size;
	}

	template<int Size, typename T>
	inline glm::vec<Size, T> LuaVec<Size, T>::GLM() const
	{
		glm::vec<Size, T> temp;
		for (int i = 0; i < Size; i++)
		{
			temp[i] = (*this)[i];
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::operator glm::vec<Size, T>() const
	{
		return this->GLM();
	}

	template<int Size, typename T>
	template<int OtherSize, typename OtherT>
	inline LuaVec<Size, T>::operator LuaVec<OtherSize, OtherT>() const
	{
		LuaVec<OtherSize, OtherT> temp;

		for (int i = 0; i < Size && i < OtherSize; i++)
		{
			temp[i] += static_cast<OtherT>((*this)[i]);
		}

		return temp;
	}

	template<int Size, typename T>
	inline T& LuaVec<Size, T>::operator[](int index)
	{
		switch (index)
		{
		case 0:
		{
			return x;
		}
		break;
		case 1:
		{
			return y;
		}
		break;
		case 2:
		{
			return z;
		}
		break;
		case 3:
		{
			return w;
		}
		break;
		default:
		{
			return x;
		}
		break;
		}
	}

	template<int Size, typename T>
	inline const T& LuaVec<Size, T>::operator[](int index) const
	{
		switch (index)
		{
		case 0:
		{
			return x;
		}
		break;
		case 1:
		{
			return y;
		}
		break;
		case 2:
		{
			return z;
		}
		break;
		case 3:
		{
			return w;
		}
		break;
		default:
		{
			return x;
		}
		break;
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator+(const LuaVec<Size, T>& other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] += other[i];
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator+(T other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] += other;
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator-(const LuaVec<Size, T>& other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] -= other[i];
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator-(T other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] -= other;
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator*(const LuaVec<Size, T>& other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] *= other[i];
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator*(T other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] *= other;
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator/(const LuaVec<Size, T>& other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] /= other[i];
		}

		return temp;
	}

	template<int Size, typename T>
	inline LuaVec<Size, T> LuaVec<Size, T>::operator/(T other)
	{
		LuaVec<Size, T> temp = (*this);

		for (int i = 0; i < Size; i++)
		{
			temp[i] /= other;
		}

		return temp;
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator+=(const LuaVec<Size, T>& other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] += other[i];
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator+=(T other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] += other;
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator-=(const LuaVec<Size, T>& other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] -= other[i];
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator-=(T other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] -= other;
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator*=(const LuaVec<Size, T>& other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] *= other[i];
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator*=(T other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] *= other;
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator/=(const LuaVec<Size, T>& other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] /= other[i];
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator/=(T other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] /= other;
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator=(const LuaVec<Size, T>& other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] = other[i];
		}
	}

	template<int Size, typename T>
	inline void LuaVec<Size, T>::operator=(T other)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] = other;
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::LuaVec(const LuaVec<Size, T>& vector)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] = vector[i];
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::LuaVec(const glm::vec<Size, T>& vector)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] = vector[i];
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::LuaVec(T scalar31, T scalar32, T scalar33, T scalar34)
	{
		if (Size >= 1)
		{
			this->x = scalar31;
		}
		if (Size >= 2)
		{
			this->y = scalar32;
		}
		if (Size >= 3)
		{
			this->z = scalar33;
		}
		if (Size >= 4)
		{
			this->w = scalar34;
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::LuaVec(T scalar31, T scalar32, T scalar33)
	{
		if (Size >= 1)
		{
			this->x = scalar31;
		}
		if (Size >= 2)
		{
			this->y = scalar32;
		}
		if (Size >= 3)
		{
			this->z = scalar33;
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::LuaVec(T scalar31, T scalar32)
	{
		if (Size >= 1)
		{
			this->x = scalar31;
		}
		if (Size >= 2)
		{
			this->y = scalar32;
		}
	}

	template<int Size, typename T>
	inline LuaVec<Size, T>::LuaVec(T scalar3)
	{
		for (int i = 0; i < Size; i++)
		{
			(*this)[i] = scalar3;
		}
	}

	using LuaVec2 = LuaVec<2, float>;
	using LuaVec3 = LuaVec<3, float>;
	using LuaVec4 = LuaVec<4, float>;
}
