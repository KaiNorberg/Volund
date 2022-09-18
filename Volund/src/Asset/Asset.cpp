#include "PCH/PCH.h"
#include "Asset.h"

namespace Volund
{
	std::string BaseAsset::GetName() const
	{
		if (this->_FilePath.contains('\\'))
		{
			return std::string(this->_FilePath.begin() + this->_FilePath.find_last_of('\\') + 1, this->_FilePath.begin() + this->_FilePath.find_last_of('.'));
		}
		else
		{
			return std::string(this->_FilePath.begin(), this->_FilePath.begin() + this->_FilePath.find_last_of('.'));
		}
	}

	std::string BaseAsset::GetFilePath() const
	{
		return this->_FilePath;
	}

	BaseAsset::BaseAsset(std::string_view FilePath)
	{
		this->_FilePath = FilePath;
		std::replace(this->_FilePath.begin(), this->_FilePath.begin(), '/', '\\');
	}
}
