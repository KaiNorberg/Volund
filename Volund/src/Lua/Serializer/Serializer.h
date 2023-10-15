#pragma once

#include "Lua/LuaTypes.h"

namespace Volund
{
	class Serializer
	{
	public:

		void WriteToFile(const std::string& filepath);

		std::string GetOutput();

		void StartTable(const std::string& name = "");
		void EndTable();

		void Insert(const std::string& name, LuaInt value);
		void Insert(const std::string& name, LuaFloat value);
		void Insert(const std::string& name, LuaBool value);
		void Insert(const std::string& name, const LuaString& value, bool asString = true);
		void Insert(const std::string& name, const LuaVec2& value);
		void Insert(const std::string& name, const LuaVec3& value);
		void Insert(const std::string& name, const Vec4& value);

		Serializer(const std::string& fileType);

	private:

		void InsertName(const std::string& name);

		void Indent();

		uint8_t m_Indentation = 1;

		std::string m_FileType;

		std::string m_Output = "";
	};
}