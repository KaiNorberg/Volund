#pragma once

namespace Volund
{
	class AssetLibrary
	{
	public:

		template <typename T>
		static Ref<T> Load(const std::string& Filepath);
		
	};

	template<typename T>
	inline Ref<T> AssetLibrary::Load(const std::string& Filepath)
	{
		static std::vector<std::pair<std::string, Ref<T>>> AssetCache;
		
		Ref<T> Return;
		for (int i = 0; i < AssetCache.size(); i++)
		{
			auto& [AssetFilepath, Referance] = AssetCache[i];

			if (AssetFilepath == Filepath)
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
			Ref<T> NewAsset = T::Create(Filepath);
			AssetCache.push_back({Filepath, NewAsset});
			return NewAsset;
		}
		else
		{
			return Return;
		}
	}
}
