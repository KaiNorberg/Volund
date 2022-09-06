#include "PCH/PCH.h"

#include "JSON.h"

namespace Volund
{
	uint64_t JSON::Size() const
	{
		return this->_JSONObject.size();
	}

	JSON JSON::Load(std::string const& FilePath)
	{
		std::ifstream File(FilePath);

		VOLUND_ASSERT(File.is_open(), "Unable to open JSON file (%s)", FilePath.c_str());

		return JSON(nlohmann::json::parse(File));
	}

	JSON const JSON::operator[](const char* Other) const
	{
		VOLUND_ASSERT(this->_JSONObject.contains(Other), "Unable to find JSON entry (%s)!", Other);

		return JSON(this->_JSONObject[Other]);
	}

	JSON const JSON::operator[](int32_t const& Other) const
	{
		VOLUND_ASSERT(Other < this->_JSONObject.size(), "Index exceeds boundary of JSON entry (%d)!", Other);

		return JSON(this->_JSONObject[Other]);
	}

	void JSON::Save(std::string const& FilePath)
	{
		std::ofstream File(FilePath);
		File << std::setw(4) << this->_JSONObject << std::endl;
	}	

	JSON::JSON(nlohmann::json const& JSONObject)
	{
		this->_JSONObject = JSONObject;
	}

}
