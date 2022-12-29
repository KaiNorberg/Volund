#include "PCH/PCH.h"
#include "Filesystem.h"

namespace Volund
{
	std::string Filesystem::LoadFile(const std::string& Filepath)
	{
		if (IsResource(Filepath))
		{
			return LoadResource(Filepath);
		}

		std::ifstream File(GetFinalPath(Filepath));
		
		if (!File)
		{
			VOLUND_WARNING("Unable to load file (%s).", Filepath.c_str());

			return "";
		}
		
		std::string Line;
		std::string Output;
		while (std::getline(File, Line))
		{
			Output += Line + '\n';
		}
		return Output;
	}

	void Filesystem::WriteFile(const std::string& Filepath, const std::string& File)
	{
		std::ofstream Stream(GetFinalPath(Filepath));

		Stream << File;
	}

	std::string Filesystem::LoadResource(const std::string& Filepath)
	{
		if (IsResource(Filepath))
		{
			return _Resources[Filepath];
		}
		else
		{
			return std::string();
		}
	}

	bool Filesystem::IsResource(const std::string& Filepath)
	{
		static Filesystem SingleTon;

		return _Resources.contains(Filepath);
	}

	void Filesystem::CreateResource(const std::string& Filepath, const char* Content)
	{
		_Resources[Filepath] = Content;
	}

	void Filesystem::AddRelativeFilepath(const std::string& Filepath)
	{
		_RelativeFilepaths.push_back(Filepath);
	}

	void Filesystem::RemoveRelativeFilepath(const std::string& Filepath)
	{
		auto it = std::find(_RelativeFilepaths.begin(), _RelativeFilepaths.end(), Filepath);

		if (it != _RelativeFilepaths.end())
		{
			_RelativeFilepaths.erase(it);
		}
	}

	std::string Filesystem::GetFinalPath(const std::string& Filepath)
	{
		if (std::filesystem::exists(Filepath))
		{
			return Filepath;
		}

		for (auto& RelativePath : _RelativeFilepaths)
		{
			std::string NewPath = RelativePath + "\\" + Filepath;

			if (std::filesystem::exists(NewPath))
			{
				return NewPath;
			}
		}

		return Filepath;
	}

	Filesystem::Filesystem()
	{
		CreateResource("Simple.vshader",
			#include "Shaders/Simple.vshader"
		);
		CreateResource("PBR.vshader",
			#include "Shaders/PBR.vshader"
		);
		CreateResource("Sphere.vobj",
			#include "Meshes/Sphere.vobj"
		);
		CreateResource("Cube.vobj",
			#include "Meshes/Cube.vobj"
		);
		CreateResource("Quad.vobj",
			#include "Meshes/Quad.vobj"
		);
	}
}
