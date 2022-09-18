#pragma once

#include "Container/Container.h"

namespace Volund
{
	class BaseAsset
	{
	public:

		std::string GetName() const;

		std::string GetFilePath() const;

		BaseAsset() = default;

		virtual ~BaseAsset() = default;

	protected:

		BaseAsset(std::string_view FilePath);

	private:

		std::string _FilePath;
	};

	template <typename T>
	class Asset : public BaseAsset
	{
	public:

		static Asset<T> Load(std::string_view FilePath);

		Ref<T> Get();

		operator Ref<T>();

		Ref<T> operator ->();

		Asset() = default;

		Asset(Ref<Asset<T>> Other);

	private:

		Asset(std::string_view FilePath);

		std::string _FilePath;

		Ref<T> _Data;

		static inline Container<BaseAsset> _AssetContainer;
	};

	template<typename T>
	inline Ref<T> Asset<T>::Get()
	{
		return this->_Data;
	}

	template<typename T>
	inline Asset<T>::operator Ref<T>()
	{
		return this->_Data;
	}

	template<typename T>
	inline Ref<T> Asset<T>::operator->()
	{
		return this->_Data;
	}

	template<typename T>
	inline Asset<T>::Asset(Ref<Asset<T>> Other)
		: BaseAsset(Other->GetFilePath())
	{
		this->_Data = Other->Get();
	}

	template<typename T>
	inline Asset<T>::Asset(std::string_view FilePath)
		: BaseAsset(FilePath)
	{
		this->_Data = T::Create(FilePath);
	}

	template<typename T>
	inline Asset<T> Asset<T>::Load(std::string_view FilePath)
	{
		if (_AssetContainer.Contains<Asset<T>>())
		{
			auto View = _AssetContainer.View<Asset<T>>();

			for (auto& CachedBaseAsset : View)
			{
				if (CachedBaseAsset->GetFilePath() == FilePath)
				{
					auto CachedAsset = std::dynamic_pointer_cast<Asset<T>>(CachedBaseAsset);
					return Asset<T>(CachedAsset);
				}
			}
		}

		auto NewAsset = Ref<Asset<T>>(new Asset<T>(FilePath));
		_AssetContainer.PushBack(NewAsset);
		return Asset<T>(NewAsset);
	}
}
