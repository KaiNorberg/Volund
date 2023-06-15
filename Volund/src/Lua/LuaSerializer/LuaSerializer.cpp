#include "PCH/PCH.h"

#include "LuaSerializer.h"

namespace Volund
{
	void LuaSerializer::WriteToFile(std::string const& filepath)
	{
		VOLUND_INFO("Writing serialized table to (%s)...", filepath.c_str());

		std::ofstream file(filepath);

		if (!file)
		{
			VOLUND_WARNING("Failed to write to (%s)!");
			return;
		}

		file << "local table =\n" + this->m_Output + "\n\nreturn table";
	}

	std::string LuaSerializer::GetOutput()
	{
		return this->m_Output;
	}

	void LuaSerializer::StartTable()
	{
		if (!this->m_Output.empty() && this->m_Output.back() == '}')
		{
			this->m_Output += ",\n";
		}
		this->Indent();
		this->m_Output += "{\n";
		this->m_Indentation += 1;
	}

	void LuaSerializer::EndTable()
	{
		this->m_Indentation -= 1;
		this->m_Output += "\n";
		this->Indent();
		this->m_Output += "}";
	}

	void LuaSerializer::Insert(std::string const& name, int value)
	{
		this->InsertName(name);
		this->m_Output += std::to_string(value) + "";
	}

	void LuaSerializer::Insert(std::string const& name, float value)
	{
		this->InsertName(name);
		this->m_Output += std::to_string(value) + "";
	}

	void LuaSerializer::Insert(std::string const& name, Vec2 const& value)
	{
		this->InsertName(name);
		this->m_Output += "Vec3:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) + ")";
	}

	void LuaSerializer::Insert(std::string const& name, Vec3 const& value)
	{
		this->InsertName(name);
		this->m_Output += "Vec3:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) +
			", " + std::to_string(value.z) + ")";
	}

	void LuaSerializer::Insert(std::string const& name, Vec4 const& value)
	{
		this->InsertName(name);
		this->m_Output += "Vec3:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) +
			", " + std::to_string(value.z) +
			", " + std::to_string(value.w) + ")";
	}

	void LuaSerializer::Insert(std::string const& name, std::string const& value, bool asString)
	{
		this->InsertName(name);
		if (asString)
		{
			this->m_Output += "\"" + value + "\"";
		}
		else
		{
			this->m_Output += value;
		}
	}

	void LuaSerializer::InsertName(std::string const& name)
	{
		if (!this->m_Output.empty() && this->m_Output.back() != '\n')
		{
			this->m_Output += ",\n";
		}
		this->Indent();
		if (name != "")
		{
			this->m_Output += name + " = ";
		}
	}

	void LuaSerializer::Indent()
	{
		for (int i = 0; i < this->m_Indentation; i++)
		{
			this->m_Output += "\t";
		}
	}
}