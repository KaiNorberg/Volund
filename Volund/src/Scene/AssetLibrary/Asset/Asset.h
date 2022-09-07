#pragma once

namespace Volund
{
	class Asset
	{
	public:

		std::string GetFilePath();

		Asset() = default;

		virtual ~Asset() = default;

	protected:

		std::string _FilePath;
	};
}


