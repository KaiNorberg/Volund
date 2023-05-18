#pragma once

namespace Volund
{
	class Serializer
	{
	public:

		void WriteToFile(std::string const& filepath);

		std::string GetOutput();

		virtual ~Serializer() = default;

	protected:

		void StartTable();

		void EndTable();

		void Insert(std::string const& name, int value);
		void Insert(std::string const& name, float value);
		void Insert(std::string const& name, Vec2 const& value);
		void Insert(std::string const& name, Vec3 const& value);
		void Insert(std::string const& name, Vec4 const& value);
		void Insert(std::string const& name, std::string const& value, bool asString = true);

	private:

		void InsertName(std::string const& name);

		void Indent();

		uint8_t m_Indentation = 0;

		std::string m_Output = "";
	};
}