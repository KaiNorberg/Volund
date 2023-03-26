#pragma once

typedef unsigned long FILEOPENDIALOGOPTIONS;

namespace Volund
{
	class Dialog
	{
	public:

		static std::string OpenFolder();

		static std::string OpenFile();

	private:

		static std::string FileDialog(FILEOPENDIALOGOPTIONS options = NULL);
	};
}