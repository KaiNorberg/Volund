#include "PCH/PCH.h"

#include "ViewportWindow.h"

void ViewportWindow::OnProcedure(const VL::Event& e)
{
	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		auto gameState = this->m_Context->GameState;

		this->m_Camera->Render(gameState, ImVec2(this->m_Size.x, this->m_Size.y));

		ImVec2 buttonSize = ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight());
		bool isPaused = this->m_Context->IsPaused();

		ImGuiAlign("#######", 1.f);

		ImGui::BeginDisabled(!isPaused);
		if (ImGui::ImageButton("PlayButton", (ImTextureID)this->m_PlayIcon->GetID(),
			buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			if (this->m_Context->IsPaused())
			{
				this->m_Context->Enqueue(EDITOR_EVENT_TYPE_PLAY);
			}
		}
		ImGui::EndDisabled();

		ImGui::SameLine();

		ImGui::BeginDisabled(isPaused);
		if (ImGui::ImageButton("PauseButton", (ImTextureID)this->m_PauseIcon->GetID(),
			buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
		{
			if (!this->m_Context->IsPaused())
			{
				this->m_Context->Enqueue(EDITOR_EVENT_TYPE_PAUSE);
			}
		}
		ImGui::EndDisabled();

		if (ImGui::BeginChild(this->GetId().c_str()))
		{
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			this->m_Size = VL::Vec2(viewportSize.x, viewportSize.y);

			if (this->m_Viewportbuffer != nullptr)
			{
				ImGui::Image(reinterpret_cast<void*>((uint64_t)this->m_Viewportbuffer->GetAttachment(0)), ImVec2(this->m_Size.x, this->m_Size.y), ImVec2(0, 1), ImVec2(1, 0));
			}
		}
		ImGui::EndChild();
	}
	break;
	case VOLUND_EVENT_TYPE_UPDATE:
	{
		float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

		if (!this->m_Context->IsPaused())
		{
			this->m_Viewportbuffer = this->m_Camera->GetSceneFramebuffer();
		}
		else
		{
			this->m_Camera->Update(this->m_Input, timeStep, this->IsWindowHovered());

			this->m_Viewportbuffer = this->m_Camera->GetEditorFramebuffer();
		}
	}
	break;
	case EDITOR_EVENT_TYPE_RESET:
	{
		this->m_Camera->Invalidate();
	}
	break;
	}
}

ViewportWindow::ViewportWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Viewport");

	this->m_Context = context;
	this->m_Camera = std::make_shared<ViewportCamera>();

	this->m_PlayIcon = VL::Texture::Create("data/icons/play.png");
	this->m_PauseIcon = VL::Texture::Create("data/icons/pause.png");
}
