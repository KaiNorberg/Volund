#pragma once

namespace Volund
{
	class AssetLibrary
	{
	public:

		template <typename T>
		static Ref<T> Load(const std::string& FilePath);
		
	};

	template<typename T>
	inline Ref<T> AssetLibrary::Load(const std::string& FilePath)
	{
		static std::vector<std::pair<std::string, Ref<T>>> AssetCache;
		
		Ref<T> Return;
		for (int i = 0; i < AssetCache.size(); i++)
		{
			auto& [AssetFilePath, Referance] = AssetCache[i];

			if (AssetFilePath == FilePath)
			{
				Return = Referance;
			}
			else
			{
				if (Referance.use_count() <= 1)
				{
					AssetCache.erase(AssetCache.begin() + i);
					i--;
				}
			}
		}

		if (Return == nullptr)
		{
			Ref<T> NewAsset = T::Create(FilePath);
			AssetCache.push_back({FilePath, NewAsset});
			return NewAsset;
		}
		else
		{
			return Return;
		}
	}
}
