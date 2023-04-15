#include "PCH/PCH.h"
#include "GameModule.h"

#include "Application/Application.h"

#include "Application/Module/WindowModule/WindowModule.h"

#include "Filesystem/Filesystem.h"

#include "DeferredTaskHandler/DeferredTaskHandler.h"

namespace Volund
{
	void GameModule::OnAttach(Application* app)
	{
		if (!app->HasModule<WindowModule>())
		{
			VOLUND_ERROR("Cant attach a GameModule to an app without a WindowModule!");
		}

		this->m_GameWindow = app->GetModule<WindowModule>()->GetWindow();
	}

	void GameModule::OnDetach()
	{

	}

	void GameModule::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_GameState != nullptr)
		{
			this->m_GameState->Procedure(e);
		}
	}

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

		DeferredTaskHandler::DeferTask([this, filepath]()
		{
			this->m_Filepath = filepath;

			this->m_GameState.reset();

			this->m_GameState = std::make_shared<GameState>(this->m_GameWindow, this->m_Filepath);
		});
	}
}