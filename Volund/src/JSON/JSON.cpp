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

		if (!File.is_open())
		{
			VOLUND_ERROR("Unable to open JSON file (%s)", FilePath);
		}

		return JSON(nlohmann::json::parse(File));
	}		

	JSON JSON::operator[](const char* Other)
	{
		if (this->_JSONObject.contains(Other))
		{
			return JSON(this->_JSONObject[Other]);
		}
		else
		{
			VOLUND_ERROR("Unable to find entry in json file (%s)!", Other);
			return JSON();
		}
	}	
		
	JSON JSON::operator[](int32_t const& Other)
	{
		if (Other < this->_JSONObject.size())
		{
			return JSON(this->_JSONObject[Other]);
		}
		else
		{
			VOLUND_ERROR("Index exceeds boundary of JSON file (%d)!", Other);
			return JSON();
		}
	}
	JSON::JSON(nlohmann::json const& JSONObject)
	{
		this->_JSONObject = JSONObject;
	}

}
