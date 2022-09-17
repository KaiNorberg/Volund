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
		Ref<T> Get(std::string_view Name);

		template <typename T>
		Ref<T> Get(uint32_t Index);

		template <typename T>
		void Erase(Ref<T> Element);

		template <typename T>
		void Erase(std::string_view Name);

		template <typename T>
		void Erase(uint32_t Index);

		template <typename T>
		Ref<T> Create(std::string_view FilePath);

		template <typename T>
		uint32_t Amount();

		template <typename T>
		bool Contains(std::string_view Name) const;

		template <typename T>
		const std::vector<Ref<Asset>>& View() const;

		template <typename T>
		VMLEntry Serialize();

		template <typename T>
		void Deserialize(VMLEntry& AssetsJSON);

		template <typename T>
		bool HasType();

		std::vector<std::vector<Ref<Asset>>>::iterator begin();
		std::vector<std::vector<Ref<Asset>>>::iterator end();

		std::vector<std::vector<Ref<Asset>>>::const_iterator begin() const;
		std::vector<std::vector<Ref<Asset>>>::const_iterator end() const;

	private:

		Container<Asset> _AssetContainer;
	};

	template <typename T>
	Ref<T> AssetLibrary::Get(std::string_view Name)
	{
		for (uint64_t i = 0; i < this->_AssetContainer.Size<T>(); i++)
		{
			if (this->_AssetContainer.Get<T>(i)->GetName() == Name)
			{
				return this->_AssetContainer.Get<T>(i);
			}
		}

		VOLUND_ERROR("Unable to find Asset (%s)!", Name.data());

		return nullptr;
	}

	template <typename T>
	Ref<T> AssetLibrary::Get(uint32_t Index)
	{
		return this->_AssetContainer.Get<T>(Index);
	}

	template<typename T>
	inline void AssetLibrary::Erase(Ref<T> Element)
	{
		for (uint64_t i = 0; i < this->_AssetContainer.Size<T>(); i++)
		{
			if (this->_AssetContainer.Get<T>(i).get() == Element.get())
			{
				this->_AssetContainer.Erase<T>(i);
				return;
			}
		}

		VOLUND_ERROR("Unable to find Asset (%s)!", Element->GetFilePath().c_str());
	}

	template<typename T>
	inline void AssetLibrary::Erase(std::string_view Name)
	{
		for (uint64_t i = 0; i < this->_AssetContainer.Size<T>(); i++)
		{
			if (this->_AssetContainer.Get<T>(i)->GetName() == Name)
			{
				this->_AssetContainer.Erase<T>(i);
				return;
			}
		}

		VOLUND_ERROR("Unable to find Asset (%s)!", Name.data());
	}

	template<typename T>
	inline void AssetLibrary::Erase(uint32_t Index)
	{
		this->_AssetContainer.Erase<T>(Index);
	}

	template <typename T>
	Ref<T> AssetLibrary::Create(std::string_view FilePath)
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

	template<typename T>
	inline bool AssetLibrary::Contains(std::string_view Name) const
	{
		for (uint64_t i = 0; i < this->_AssetContainer.Size<T>(); i++)
		{
			if (this->_AssetContainer.Get<T>(i)->GetName() == Name)
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	inline const std::vector<Ref<Asset>>& AssetLibrary::View() const
	{
		return this->_AssetContainer.View<T>();
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
			Ref<T> NewAsset = std::make_shared<T>(this, AssetsVML[i]);

			this->_AssetContainer.PushBack(NewAsset);
		}
	}

	template <typename T>
	bool AssetLibrary::HasType()
	{
		return this->_AssetContainer.Contains<T>(0);
	}
}
