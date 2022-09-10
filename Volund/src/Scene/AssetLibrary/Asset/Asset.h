#pragma once

namespace Volund
{
	class AssetLibrary;

	class Asset
	{
	public:
		std::string GetFilePath();

		Asset() = default;

		virtual ~Asset() = default;

	protected:

		AssetLibrary* _Parent = nullptr;

		std::string _FilePath;
	};
}
