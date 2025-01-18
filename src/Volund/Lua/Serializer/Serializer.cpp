#include "Serializer.h"

#include <fstream>
#include <algorithm>

namespace Volund
{
	void Serializer::WriteToFile(std::string const& filepath)
	{
		VOLUND_INFO("Writing serialized table to (%s)...", filepath.c_str());

		std::ofstream file(filepath);

		if (!file)
		{
			VOLUND_WARNING("Failed to write to (%s)!", filepath.c_str());
			return;
		}

		if (this->m_Output.empty())
		{
			file << "local table =\n{\n\n}\n\nreturn table";
		}
		else
		{
			file <<
				(std::string)"local table =\n" +
				"{\n" +
				"	" + VOLUND_SERIAL_FILE_TYPE + " = \"" + this->m_FileType + "\",\n" +
				"	" + VOLUND_SERIAL_DATA + " = \n" +
					this->m_Output +
				"\n}" +
				"\n\nreturn table";
		}
	}

	std::string Serializer::GetOutput()
	{
		return this->m_Output;
	}

	void Serializer::StartTable(std::string const& name)
	{
		if (!this->m_Output.empty() && !this->m_Output.ends_with("{\n"))
		{
			this->m_Output += ",\n";
		}
		if (name != "")
		{
			this->Indent();
			this->m_Output += name + " =\n";
		}
		this->Indent();
		this->m_Output += "{\n";
		this->m_Indentation += 1;
	}

	void Serializer::EndTable()
	{
		this->m_Indentation -= 1;
		this->m_Output += "\n";
		this->Indent();
		this->m_Output += "}";
	}

	void Serializer::Insert(std::string const& name, LuaInt value)
	{
		this->InsertName(name);
		this->m_Output += std::to_string(value) + "";
	}

	void Serializer::Insert(std::string const& name, LuaBool value)
	{
		this->InsertName(name);
		this->m_Output += std::to_string(value) + "";
	}

	void Serializer::Insert(std::string const& name, LuaFloat value)
	{
		this->InsertName(name);
		this->m_Output += std::to_string(value) + "";
	}

	void Serializer::Insert(std::string const& name, const LuaVec2& value)
	{
		this->InsertName(name);
		this->m_Output += "Vec2:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) + ")";
	}

	void Serializer::Insert(std::string const& name, const LuaVec3& value)
	{
		this->InsertName(name);
		this->m_Output += "Vec3:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) +
			", " + std::to_string(value.z) + ")";
	}

	void Serializer::Insert(std::string const& name, const Vec4& value)
	{
		this->InsertName(name);
		this->m_Output += "Vec4:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) +
			", " + std::to_string(value.z) +
			", " + std::to_string(value.w) + ")";
	}

	void Serializer::Insert(std::string const& name, const LuaString& value, bool asString)
	{
		this->InsertName(name);

		std::string formatedValue = value;
		std::replace(formatedValue.begin(), formatedValue.end(), '\\', '/');

		if (asString)
		{
			this->m_Output += "\"" + formatedValue + "\"";
		}
		else
		{
			this->m_Output += formatedValue;
		}
	}

	Serializer::Serializer(std::string const& fileType)
	{
		this->m_FileType = fileType;
	}

	void Serializer::InsertName(std::string const& name)
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

	void Serializer::Indent()
	{
		for (int i = 0; i < this->m_Indentation; i++)
		{
			this->m_Output += "\t";
		}
	}
}
