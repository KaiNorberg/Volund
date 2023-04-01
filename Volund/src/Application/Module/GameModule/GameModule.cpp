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
		return this->m_Filepath;
	}

	Ref<Scene> GameModule::GetScene()
	{
		if (this->m_GameState != nullptr)
		{
			return this->m_GameState->GetScene();
		}
		else
		{
			return nullptr;
		}
	}

	void GameModule::LoadNewState(const std::string& filepath)
	{
		std::unique_lock lock(this->m_Mutex);

		DelayedTaskHandler::DelayTask([this, filepath]()
		{
			if (!this->m_Filepath.empty())
			{
				const std::string parentPath = std::filesystem::path(this->m_Filepath).parent_path().string();
				Filesystem::RemoveRelativeFilepath(parentPath);
			}

			this->m_Filepath = filepath;

			const std::string parentPath = std::filesystem::path(filepath).parent_path().string();
			Filesystem::AddRelativeFilepath(parentPath);

			this->m_GameState.reset();

			try
			{
				this->m_GameState = std::make_shared<GameState>(this->m_GameWindow);
				this->m_GameState->GetLuaState()->ScriptFile(this->m_Filepath);
			}
			catch (sol::error e)
			{
				VOLUND_WARNING(e.what());
			}
		});
	}

	void GameModule::OnAttach(Application* app)
	{
		if (!app->HasModule<WindowModule>())
		{
			VOLUND_ERROR("Cant attach LuaModule to an app without a WindowModule!");
		}

		this->m_GameWindow = app->GetModule<WindowModule>()->GetWindow();
	}

	void GameModule::OnDetach()
	{
		if (!this->m_Filepath.empty())
		{
			const std::string parentPath = std::filesystem::path(this->m_Filepath).parent_path().string();
			Filesystem::RemoveRelativeFilepath(parentPath);
		}
	}

	void GameModule::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_GameState != nullptr)
		{
			this->m_GameState->Procedure(e);
		}
	}
}