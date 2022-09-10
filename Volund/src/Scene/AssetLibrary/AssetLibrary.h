#pragma once

#include "Asset/Asset.h"

#include "VML/VML.h"

namespace Volund
{
	class AssetLibrary
	{
	public:
		template <typename T>
		Ref<T> GetAsset(const std::string& FilePath);

		template <typename T>
		Ref<T> GetAsset(uint32_t Index);

		template <typename T>
		Ref<T> Create(const std::string& FilePath);

		template <typename T>
		uint32_t AssetAmount();

		template <typename T>
		VMLEntry Serialize();

		template <typename T>
		void Deserialize(VMLEntry& AssetsJSON);

		template <typename T>
		bool HasAssetType();

	private:
		template <typename T>
		uint32_t GetTypeID();

		static inline uint32_t _NewTypeID = 0;

		std::vector<std::vector<Ref<Asset>>> _Assets;
	};

	template <typename T>
	Ref<T> AssetLibrary::GetAsset(const std::string& FilePath)
	{
		static uint64_t TypeID = GetTypeID<T>();

		for (uint64_t i = 0; i < this->_Assets[TypeID].size(); i++)
		{
			if (this->_Assets[TypeID][i]->GetFilePath() == FilePath)
			{
				return std::dynamic_pointer_cast<T>(this->_Assets[TypeID][i]);
			}
		}

		VOLUND_ERROR("Unable to find Asset (%s)!", FilePath.c_str());

		return nullptr;
	}

	template <typename T>
	Ref<T> AssetLibrary::GetAsset(uint32_t Index)
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasAssetType<T>())
		{
			VOLUND_ERROR("Unable to find Asset!");
		}

		return this->_Assets[TypeID][Index];
	}

	template <typename T>
	Ref<T> AssetLibrary::Create(const std::string& FilePath)
	{
		static uint64_t TypeID = GetTypeID<T>();

		while (this->_Assets.size() <= TypeID)
		{
			this->_Assets.push_back(std::vector<Ref<Asset>>());
		}

		Ref<T> NewAsset = std::make_shared<T>(this, FilePath);

		this->_Assets[TypeID].push_back(NewAsset);

		return NewAsset;
	}

	template <typename T>
	uint32_t AssetLibrary::AssetAmount()
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasAssetType<T>())
		{
			VOLUND_ERROR("Unable to find Asset!");
		}

		return this->_Assets[TypeID];
	}

	template <typename T>
	VMLEntry AssetLibrary::Serialize()
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasAssetType<T>())
		{
			return VMLEntry();
		}

		VMLEntry Result;
		for (uint64_t i = 0; i < this->_Assets[TypeID].size(); i++)
		{
			Result.PushBack(this->_Assets[TypeID][i]->GetFilePath());
		}
		return Result;
	}

	template <typename T>
	void AssetLibrary::Deserialize(VMLEntry& AssetsVML)
	{
		static uint64_t TypeID = GetTypeID<T>();

		while (this->_Assets.size() <= TypeID)
		{
			this->_Assets.push_back(std::vector<Ref<Asset>>());
		}

		for (uint32_t i = 0; i < AssetsVML.Size(); i++)
		{
			this->_Assets[TypeID].push_back(std::make_shared<T>(this, AssetsVML[i]));
		}
	}

	template <typename T>
	bool AssetLibrary::HasAssetType()
	{
		static uint64_t TypeID = GetTypeID<T>();

		return TypeID < this->_Assets.size() && !this->_Assets[TypeID].empty();
	}

	template <typename T>
	uint32_t AssetLibrary::GetTypeID()
	{
		static uint32_t ID = _NewTypeID++;

		return ID;
	}
}
