#include "PCH/PCH.h"
#include "GameModule.h"

#include "Application/Application.h"

#include "Application/Module/WindowModule/WindowModule.h"

#include "Filesystem/Filesystem.h"

#include "DelayedTaskHandler/DelayedTaskHandler.h"

namespace Volund
{
	std::string GameModule::GetFilepath()
	{
		return this->_Filepath;
	}

	Ref<Scene> GameModule::GetScene()
	{
		if (this->_GameState != nullptr)
		{
			return this->_GameState->GetScene();
		}
		else
		{
			return nullptr;
		}
	}

	void GameModule::NewState(const std::string& Filepath)
	{
		std::unique_lock Lock(this->_Mutex);

		DelayedTaskHandler::DelayTask([this, Filepath]()
		{
			if (!this->_Filepath.empty())
			{
				std::string ParentPath = std::filesystem::path(this->_Filepath).parent_path().string();
				Filesystem::RemoveRelativeFilepath(ParentPath);
			}

			this->_Filepath = Filepath;

			std::string ParentPath = std::filesystem::path(Filepath).parent_path().string();
			Filesystem::AddRelativeFilepath(ParentPath);

			this->_GameState.reset();

			try
			{
				this->_GameState = std::make_shared<GameState>(this->_GameWindow);
				this->_GameState->GetLuaState()->ScriptFile(this->_Filepath);
			}
			catch (sol::error E)
			{
				VOLUND_WARNING(E.what());
			}
		});
	}

	void GameModule::OnAttach(Application* App)
	{
		if (!App->HasModule<WindowModule>())
		{
			VOLUND_ERROR("Cant attach LuaModule to an app without a WindowModule!");
		}

		this->_GameWindow = App->GetModule<WindowModule>()->GetWindow();
	}

	void GameModule::OnDetach()
	{
		if (!this->_Filepath.empty())
		{
			std::string ParentPath = std::filesystem::path(this->_Filepath).parent_path().string();
			Filesystem::RemoveRelativeFilepath(ParentPath);
		}
	}

	void GameModule::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->_GameState != nullptr)
		{
			this->_GameState->Procedure(E);
		}
	}
}