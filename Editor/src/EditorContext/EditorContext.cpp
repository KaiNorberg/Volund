#include "PCH/PCH.h"
#include "EditorContext.h"

#include "Lua/Serializer/SceneSerializer/SceneSerializer.h"

VL::Ref<VL::Window> EditorContext::GetWindow()
{
	return this->m_Window;
}

VL::Ref<VL::Scene> EditorContext::GetScene()
{
	if (this->m_State != nullptr)
	{
		return this->m_State->GetScene();
	}
	else
	{
		return nullptr;
	}
}

std::string EditorContext::GetSceneFilepath()
{
	return this->m_SceneFilepath;
}

void EditorContext::SaveScene(const std::string& filepath)
{
	if (this->GetScene() == nullptr)
	{
		return;
	}

	std::unique_lock lock(this->m_Mutex);

	VL::DeferredTaskHandler::DeferTask([this, filepath]()
	{
		this->m_SceneFilepath = filepath;

		auto sceneSerializer = VL::SceneSerializer(this->GetScene());

		sceneSerializer.WriteToFile(filepath);
	});
}

void EditorContext::LoadNewScene(const std::string& filepath)
{
	std::unique_lock lock(this->m_Mutex);

	VL::DeferredTaskHandler::DeferTask([this, filepath]()
	{
		this->m_SceneFilepath = filepath;

		this->m_State.reset();

		auto luaGameState = VL::LuaGameState(this->m_Window, this->m_SceneFilepath);

		this->m_State = luaGameState.Get();
	});
}

EditorContext::EditorContext(VL::Ref<VL::Window> window)
{
	this->m_Window = window;
}
