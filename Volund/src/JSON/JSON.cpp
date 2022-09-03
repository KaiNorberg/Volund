#include "PCH/PCH.h"

#include "JSON.h"

namespace Volund
{
	uint64_t JSON::Size()
	{
		return this->_JSONObject.size();
	}

	JSON JSON::Load(std::string const& FilePath)
	{
		std::ifstream File(FilePath);

		VOLUND_ASSERT(File.is_open(), "Unable to open JSON file (%s)", FilePath.c_str());

		return JSON(nlohmann::json::parse(File));
	}		

	JSON JSON::operator[](const char* Other)
	{
		VOLUND_ASSERT(this->_JSONObject.contains(Other), "Unable to find entry in json file (%s)!", Other);

		return JSON(this->_JSONObject[Other]);
	}	
		
	JSON JSON::operator[](int32_t const& Other)
	{
		VOLUND_ASSERT(Other < this->_JSONObject.size(), "Index exceeds boundary of JSON file (%d)!", Other);

		return JSON(this->_JSONObject[Other]);
	}

	JSON::JSON(nlohmann::json const& JSONObject)
	{
		this->_JSONObject = JSONObject;
	}

}
