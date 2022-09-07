#pragma once

#include "Asset/Asset.h"

namespace Volund
{
	class AssetLibrary
	{
	public:

		template<typename T>
		Ref<T> GetAsset(std::string const& FilePath);

		template<typename T>
		Ref<T> GetAsset(uint32_t Index);

		template<typename T>
		Ref<T> Create(std::string const& FilePath);

		template<typename T>
		uint32_t AssetAmount();

		template<typename T>
		JSON Serialize();

		template<typename T>
		void Deserialize(JSON const& AssetsJSON);

		template<typename T>
		bool HasAssetType();

	private:

		template<typename T>
		uint32_t GetTypeID();

		static inline uint32_t _NewTypeID = 0;

		std::vector<std::vector<Ref<Asset>>> _Assets;
	};	

	template<typename T>
	inline Ref<T> Volund::AssetLibrary::GetAsset(std::string const& FilePath)
	{
		static uint64_t TypeID = GetTypeID<T>();

		for (int i = 0; i < this->_Assets[TypeID].size(); i++)
		{
			if (this->_Assets[TypeID][i]->GetFilePath() == FilePath)
			{
				return std::dynamic_pointer_cast<T>(this->_Assets[TypeID][i]);
			}
		}

		VOLUND_ERROR("Unable to find Asset (%s)!", FilePath.c_str());

		return nullptr;
	}

	template<typename T>
	inline Ref<T> AssetLibrary::GetAsset(uint32_t Index)
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasAssetType<T>())
		{
			VOLUND_ERROR("Unable to find Asset!");
		}

		return this->_Assets[TypeID][Index];
	}

	template<typename T>
	inline Ref<T> Volund::AssetLibrary::Create(std::string const& FilePath)
	{
		static uint64_t TypeID = GetTypeID<T>();

		while (this->_Assets.size() <= TypeID)
		{
			this->_Assets.push_back(std::vector<Ref<Asset>>());
		}

		Ref<T> NewAsset = Ref<T>(new T(this, FilePath));

		this->_Assets[TypeID].push_back(NewAsset);

		return NewAsset;
	}

	template<typename T>
	inline uint32_t Volund::AssetLibrary::AssetAmount()
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasAssetType<T>())
		{
			VOLUND_ERROR("Unable to find Asset!");
		}

		return this->_Assets[TypeID];
	}

	template<typename T>
	inline JSON Volund::AssetLibrary::Serialize()
	{
		static uint64_t TypeID = GetTypeID<T>();

		if (!this->HasAssetType<T>())
		{
			return JSON();
		}

		JSON AssetsJSON = {};
		for (int i = 0; i < this->_Assets[TypeID].size(); i++)
		{
			AssetsJSON.PushBack(this->_Assets[TypeID][i]->GetFilePath());
		}
		return AssetsJSON;
	}

	template<typename T>
	inline void Volund::AssetLibrary::Deserialize(JSON const& AssetsJSON)
	{
		static uint64_t TypeID = GetTypeID<T>();

		while (this->_Assets.size() <= TypeID)
		{
			this->_Assets.push_back(std::vector<Ref<Asset>>());
		}

		for (int i = 0; i < AssetsJSON.Size(); i++)
		{
			this->_Assets[TypeID].push_back(Ref<T>(new T(this, AssetsJSON[i])));
		}
	}

	template<typename T>
	inline bool AssetLibrary::HasAssetType()
	{
		static uint64_t TypeID = GetTypeID<T>();

		return TypeID < this->_Assets.size() && !this->_Assets[TypeID].empty();
	}

	template<typename T>
	inline uint32_t AssetLibrary::GetTypeID()
	{
		static uint32_t ID = _NewTypeID++;

		return ID;
	}
}