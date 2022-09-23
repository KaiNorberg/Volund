#pragma once

namespace Volund
{
	class FileDialog
	{
	public:
		static std::string OpenFile(const char* Filter, Volund::Ref<Volund::Window> Owner);

		static std::string SaveFile(const char* Filter, Volund::Ref<Volund::Window> Owner);
	};
}