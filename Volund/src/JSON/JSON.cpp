#include "PCH/PCH.h"

#include "JSON.h"

namespace Volund
{
	uint64_t JSON::Size() const
	{
		return this->_JSONObject.size();
	}

	JSON JSON::Load(const std::string& FilePath)
	{
		std::ifstream File(FilePath);

		VOLUND_ASSERT(File.is_open(), "Unable to open JSON file (%s)", FilePath.c_str());

		return JSON(nlohmann::json::parse(File));
	}

	const JSON JSON::operator[](const char* Other) const
	{
		VOLUND_ASSERT(this->_JSONObject.contains(Other), "Unable to find JSON entry (%s)!", Other);

		return JSON(this->_JSONObject[Other]);
	}

	const JSON JSON::operator[](const int32_t& Other) const
	{
		VOLUND_ASSERT(Other < this->_JSONObject.size(), "Index exceeds boundary of JSON entry (%d)!", Other);

		return JSON(this->_JSONObject[Other]);
	}

	void JSON::Save(const std::string& FilePath) const
	{
		std::ofstream File(FilePath);
		File << std::setw(4) << this->_JSONObject << std::endl;
	}

	JSON::JSON(const nlohmann::json& JSONObject)
	{
		this->_JSONObject = JSONObject;
	}
}
