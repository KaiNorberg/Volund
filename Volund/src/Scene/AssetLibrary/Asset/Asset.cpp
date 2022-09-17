#include "PCH/PCH.h"
#include "Asset.h"

namespace Volund
{
	std::string Asset::GetName()
	{
		if (this->_FilePath.contains('\\'))
		{
			return std::string(this->_FilePath.begin() + this->_FilePath.find_last_of('\\') + 1, this->_FilePath.begin() + this->_FilePath.find_last_of('.'));
		}
		else if (this->_FilePath.contains('/'))
		{
			return std::string(this->_FilePath.begin() + this->_FilePath.find_last_of('/') + 1, this->_FilePath.begin() + this->_FilePath.find_last_of('.'));
		}
		else
		{
			return std::string(this->_FilePath.begin(), this->_FilePath.begin() + this->_FilePath.find_last_of('.'));
		}
	}

	std::string Asset::GetFilePath()
	{
		return this->_FilePath;
	}
}
