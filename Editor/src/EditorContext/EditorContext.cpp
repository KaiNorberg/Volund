#include "PCH/PCH.h"
#include "EditorContext.h"

#include "ImGuiStyles.h"

void EditorContext::OnAttach(VL::Application* app)
{
	if (!app->HasModule<VL::WindowModule>())
	{
		VOLUND_ERROR("Cant attach a GameModule to an app without a WindowModule!");
	}

	this->m_GameWindow = app->GetModule<VL::WindowModule>()->GetWindow();
	this->m_Dispatcher = app->GetDispatcher();

	SetDefaultImGuiStyle();
}

void EditorContext::OnDetach()
{
}

void EditorContext::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	switch (e.Type)
	{
	case EDITOR_EVENT_TYPE_RELOAD_SCENE:
	{
		const auto scene = this->GetScene();
		if (scene != nullptr)
		{
			this->LoadScene(this->GetScenePath());
		}
	}
	break;
	case EDITOR_EVENT_TYPE_LOAD_SCENE:
	{
		const std::string filepath = VL::Dialog::OpenFile(this->m_GameWindow);
		if (!filepath.empty())
		{
			this->LoadScene(filepath);
		}
	}
	break;
	case EDITOR_EVENT_TYPE_SAVE_SCENE:
	{		
		const std::string filepath = this->GetScenePath();
		if (!filepath.empty())
		{
			this->SaveScene(filepath);
		}
	}
	break;
	case EDITOR_EVENT_TYPE_NEW_SCENE:
	{
		const std::string filepath = VL::Dialog::OpenFolder(this->m_GameWindow);

		if (!filepath.empty())
		{
			VL::LuaSerializer serializer(VOLUND_SERIAL_FILE_TYPE_SCENE);
			serializer.WriteToFile(filepath + "/scene.lua");

			this->LoadScene(filepath + "/scene.lua");
		}
	}
	break;
	default:
	{
		if (this->m_GameState == nullptr || this->m_Paused)
		{
			return;
		}

		this->m_GameState->Procedure(e);
	}
	break;
	}
}

bool EditorContext::IsPaused()
{
	return this->m_Paused;
}

void EditorContext::Play()
{
	if (this->m_GameState == nullptr || !this->m_Paused)
	{
		return;
	}

	this->SaveScene(this->m_GameState->GetScenePath());

	SetDarkImGuiStyle();

	this->m_Paused = false;
}

void EditorContext::Pause()
{
	if (this->m_GameState == nullptr || this->m_Paused)
	{
		return;
	}	

	this->m_Paused = true;

	this->LoadScene(this->m_GameState->GetScenePath());

	SetDefaultImGuiStyle();
}

std::string EditorContext::GetScenePath()
{
	if (this->m_GameState != nullptr)
	{
		return this->m_GameState->GetScenePath();
	}
	else
	{
		return "";
	}
}

std::string EditorContext::GetParentPath()
{
	if (this->m_GameState != nullptr)
	{
		return this->m_GameState->GetParentPath();
	}
	else
	{
		return "";
	}
}

VL::Ref<VL::AssetManager> EditorContext::GetAssetmanager()
{
	if (this->m_GameState != nullptr)
	{
		return this->m_GameState->GetAssetManager();
	}
	else
	{
		return nullptr;
	}
}

VL::Ref<VL::Scene> EditorContext::GetScene()
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

VL::Ref<VL::Window> EditorContext::GetWindow()
{
	return this->m_GameWindow;
}

void EditorContext::LoadScene(const std::string& filepath)
{
	std::unique_lock lock(this->m_Mutex);

	if (!this->m_Paused)
	{
		VOLUND_WARNING("Cant load a new scene while paused!");
		return;
	}

	this->SelectedEntity = 1;
	this->m_GameState = std::make_shared<VL::GameState>(this->m_Dispatcher, filepath);
}

void EditorContext::SaveScene(const std::string& filepath)
{
	if (this->GetScene() == nullptr)
	{
		VOLUND_WARNING("No scene is loaded!");
		return;
	}
	
	this->GetAssetmanager()->Serialize(this->GetScene(), filepath);
}