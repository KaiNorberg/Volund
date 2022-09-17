#include "PCH/PCH.h"

#include "AssetLibrary.h"

namespace Volund
{
	inline std::vector<std::vector<Ref<Asset>>>::iterator AssetLibrary::begin()
	{
		return this->_AssetContainer.begin();
	}

	inline std::vector<std::vector<Ref<Asset>>>::iterator AssetLibrary::end()
	{
		return this->_AssetContainer.end();
	}

	inline std::vector<std::vector<Ref<Asset>>>::const_iterator AssetLibrary::begin() const
	{
		return this->_AssetContainer.begin();
	}

	inline std::vector<std::vector<Ref<Asset>>>::const_iterator AssetLibrary::end() const
	{
		return this->_AssetContainer.end();
	}
}
