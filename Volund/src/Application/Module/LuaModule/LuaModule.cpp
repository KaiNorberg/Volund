#include "PCH/PCH.h"
#include "LuaModule.h"

#include "Application/Application.h"

#include "Application/Module/WindowModule/WindowModule.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	std::string LuaModule::GetFilepath()
	{
		return this->_Filepath;
	}

	Ref<Scene> LuaModule::GetScene()
	{
		if (this->_LuaState != nullptr)
		{
			return this->_LuaState->GetScene();
		}
		else
		{
			return nullptr;
		}
	}

	void LuaModule::LoadScene(const std::string& Filepath)
	{
		auto NewScene = std::make_shared<Scene>();
		auto AppWindow = this->_App->GetModule<WindowModule>()->GetWindow();

		if (!this->_Filepath.empty())
		{
			std::string ParentPath = std::filesystem::path(this->_Filepath).parent_path().string();
			Filesystem::RemoveRelativeFilepath(ParentPath);
		}

		this->_Filepath = Filepath;

		std::string ParentPath = std::filesystem::path(Filepath).parent_path().string();
		Filesystem::AddRelativeFilepath(ParentPath);

		try
		{
			this->_LuaState = std::make_shared<LuaState>(NewScene, AppWindow);
			this->_LuaState->ScriptFile(this->_Filepath);
		}
		catch (sol::error E)
		{
			VOLUND_WARNING(E.what());
		}
	}

	void LuaModule::OnAttach(Application* App)
	{
		this->_App = App;

		if (!App->HasModule<WindowModule>())
		{
			VOLUND_ERROR("Cant attach LuaModule to an app without a WindowModule!");
		}
	}

	void LuaModule::OnDetach()
	{
		if (!this->_Filepath.empty())
		{
			std::string ParentPath = std::filesystem::path(this->_Filepath).parent_path().string();
			Filesystem::RemoveRelativeFilepath(ParentPath);
		}
	}

	void LuaModule::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->_LuaState != nullptr)
		{
			this->_LuaState->Procedure(E);
		}
	}
}