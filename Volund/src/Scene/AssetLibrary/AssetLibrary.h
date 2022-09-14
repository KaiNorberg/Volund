#pragma once

#include "Asset/Asset.h"

#include "VML/VML.h"

#include "Container/Container.h"

namespace Volund
{
	class AssetLibrary
	{
	public:
		template <typename T>
		Ref<T> Get(const std::string& FilePath);

		template <typename T>
		Ref<T> Get(uint32_t Index);

		template <typename T>
		Ref<T> Create(const std::string& FilePath);

		template <typename T>
		uint32_t Amount();

		template <typename T>
		VMLEntry Serialize();

		template <typename T>
		void Deserialize(VMLEntry& AssetsJSON);

		template <typename T>
		bool HasType();

	private:

		Container<Asset> _AssetContainer;
	};

	template <typename T>
	Ref<T> AssetLibrary::Get(const std::string& FilePath)
	{
		for (uint64_t i = 0; i < this->_AssetContainer.Size<T>(); i++)
		{
			if (this->_AssetContainer.Get<T>(i)->GetFilePath() == FilePath)
			{
				return this->_AssetContainer.Get<T>(i);
			}
		}

		VOLUND_ERROR("Unable to find Asset (%s)!", FilePath.c_str());

		return nullptr;
	}

	template <typename T>
	Ref<T> AssetLibrary::Get(uint32_t Index)
	{
		return this->_AssetContainer.Get<T>(Index);
	}

	template <typename T>
	Ref<T> AssetLibrary::Create(const std::string& FilePath)
	{
		Ref<T> NewAsset = std::make_shared<T>(this, FilePath);

		this->_AssetContainer.PushBack(NewAsset);

		return NewAsset;
	}

	template <typename T>
	uint32_t AssetLibrary::Amount()
	{
		return this->_AssetContainer.Size<T>();
	}

	template <typename T>
	VMLEntry AssetLibrary::Serialize()
	{
		if (!this->HasType<T>())
		{
			return VMLEntry();
		}

		VMLEntry Result;
		for (uint64_t i = 0; i < this->_AssetContainer.Size<T>(); i++)
		{
			Result.PushBack(this->_AssetContainer.Get<T>(i)->GetFilePath());
		}
		return Result;
	}

	template <typename T>
	void AssetLibrary::Deserialize(VMLEntry& AssetsVML)
	{
		for (uint32_t i = 0; i < AssetsVML.Size(); i++)
		{
			this->_AssetContainer.PushBack(std::make_shared<T>(this, AssetsVML[i]));
		}
	}

	template <typename T>
	bool AssetLibrary::HasType()
	{
		return this->_AssetContainer.Contains<T>(0);
	}
}
