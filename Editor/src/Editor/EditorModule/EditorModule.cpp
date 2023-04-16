#include "PCH/PCH.h"
#include "EditorModule.h"

VL::Ref<VL::Scene> EditorModule::GetScene()
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

std::string EditorModule::GetFilepath()
{
	return this->m_Filepath;
}

void EditorModule::OnAttach(VL::Application* app)
{
	if (!app->HasModule<VL::WindowModule>())
	{
		VOLUND_ERROR("Cant attach a editorModule to an app without a WindowModule!");
	}

	this->m_GameWindow = app->GetModule<VL::WindowModule>()->GetWindow();
}

void EditorModule::OnDetach()
{
}

void EditorModule::Procedure(const VL::Event& e)
{
	if (e.Type == VL::EventType::Update)
	{
		return;
	}

	if (this->m_GameState != nullptr)
	{
		this->m_GameState->Procedure(e);
	}
}

void EditorModule::LoadNewState(const std::string& filepath)
{
	std::unique_lock lock(this->m_Mutex);

	VL::DeferredTaskHandler::DeferTask([this, filepath]()
	{
		this->m_Filepath = filepath;

		this->m_GameState.reset();

		this->m_GameState = std::make_shared<VL::GameState>(this->m_GameWindow, this->m_Filepath);
	});
}
