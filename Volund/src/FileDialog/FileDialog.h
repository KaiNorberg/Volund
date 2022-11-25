#pragma once

typedef unsigned long FILEOPENDIALOGOPTIONS;

namespace Volund
{
	class FileDialog
	{
	public:

		static std::string OpenFolder();

		static std::string OpenFile();

	private:

		static std::string OpenDialog(FILEOPENDIALOGOPTIONS Options = NULL);
	};
}