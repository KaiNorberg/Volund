#include "PCH/PCH.h"
#include "Serializer.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	void Serializer::WriteToFile(std::string const& filepath)
	{
		VOLUND_INFO("Writing serialized table to %s", filepath.c_str());

		Filesystem::Write(filepath, "local table =\n" + this->m_Output + "\n\nreturn table");
	}

	std::string Serializer::GetOutput()
	{
		return this->m_Output;
	}

	void Serializer::StartTable()
	{
		if (!this->m_Output.empty() && this->m_Output.back() == '}')
		{
			this->m_Output += ",\n";
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

	void Serializer::Insert(std::string const& name, int value)
	{
		this->InsertName(name);

		this->m_Output += std::to_string(value) + "";
	}

	void Serializer::Insert(std::string const& name, float value)
	{
		this->InsertName(name);

		this->m_Output += std::to_string(value) + "";
	}

	void Serializer::Insert(std::string const& name, Vec2 const& value)
	{
		this->InsertName(name);

		this->m_Output += "Vec3:new(" + std::to_string(value.x) + 
			", " + std::to_string(value.y) + ")";
	}

	void Serializer::Insert(std::string const& name, Vec3 const& value)
	{
		this->InsertName(name);

		this->m_Output += "Vec3:new(" + std::to_string(value.x) + 
			", " + std::to_string(value.y) + 
			", " + std::to_string(value.z) + ")";
	}

	void Serializer::Insert(std::string const& name, Vec4 const& value)
	{
		this->InsertName(name);

		this->m_Output += "Vec3:new(" + std::to_string(value.x) +
			", " + std::to_string(value.y) +
			", " + std::to_string(value.z) +
			", " + std::to_string(value.w) + ")";
	}

	void Serializer::Insert(std::string const& name, std::string const& value, bool asString)
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