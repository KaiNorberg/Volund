#include "PCH/PCH.h"
#include "EditorContext.h"

#include "Lua/Serializer/SceneSerializer/SceneSerializer.h"

#include "ImGuiStyles.h"

void EditorContext::OnAttach(VL::Application* app)
{
	if (!app->HasModule<VL::WindowModule>())
	{
		VOLUND_ERROR("Cant attach a GameModule to an app without a WindowModule!");
	}

	this->m_GameWindow = app->GetModule<VL::WindowModule>()->GetWindow();

	SetDefaultImGuiStyle();
}

void EditorContext::OnDetach()
{
}

void EditorContext::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	if (this->m_GameState == nullptr || this->m_Paused)
	{
		return;
	}

	this->m_GameState->Procedure(e);
}

bool EditorContext::IsPaused()
{
	return this->m_Paused;
}

void EditorContext::Play()
{
	if (!this->m_Paused)
	{
		return;
	}
	this->m_Paused = false;

	this->SaveScene(this->m_Filepath);

	SetDarkImGuiStyle();
}

void EditorContext::Pause()
{
	if (this->m_Paused)
	{
		return;
	}	
	this->m_Paused = true;

	this->LoadScene(this->m_Filepath);

	SetDefaultImGuiStyle();
}

std::string EditorContext::GetFilepath()
{
	return this->m_Filepath;
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

	VL::DeferredTaskHandler::DeferTask([this, filepath]()
	{
		this->m_Filepath = filepath;

		this->m_GameState.reset();

		auto luaGameState = VL::LuaGameState(this->m_GameWindow, this->m_Filepath);

		this->m_GameState = luaGameState.Get();
	});
}

void EditorContext::SaveScene(const std::string& filepath)
{
	if (this->GetScene() == nullptr)
	{
		VOLUND_WARNING("No scene is loaded!");
		return;
	}

	VL::DeferredTaskHandler::DeferTask([this, filepath]()
	{
		auto sceneSerializer = VL::SceneSerializer(this->GetScene());

		sceneSerializer.WriteToFile(filepath);
	});
}