#pragma once

#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
	class LuaSerializer
	{
	public:

		void WriteToFile(std::string const& filepath);

		std::string GetOutput();

		void StartTable(std::string const& name = "");
		void EndTable();

		void Insert(std::string const& name, int value);
		void Insert(std::string const& name, float value);
		void Insert(std::string const& name, double value);
		void Insert(std::string const& name, Vec2 const& value);
		void Insert(std::string const& name, Vec3 const& value);
		void Insert(std::string const& name, Vec4 const& value);
		void Insert(std::string const& name, std::string const& value, bool asString = true);

		LuaSerializer(const std::string& fileType);

	private:

		void InsertName(std::string const& name);

		void Indent();

		uint8_t m_Indentation = 1;

		std::string m_FileType;

		std::string m_Output = "";
	};
}