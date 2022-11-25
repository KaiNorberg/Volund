#include "PCH/PCH.h"

#include "Editor.h"

#include "Widget/OutputWidget/OutputWidget.h"
#include "Widget/ViewportWidget/ViewportWidget.h"

void Editor::OnRun()
{
	VL::RenderingAPI::Select(VL::GraphicsAPI::OPENGL);

	this->AttachModule(new VL::WindowModule());
	this->AttachModule(new VL::ImGuiModule());

	VL::RenderingAPI::Init();
	VL::Renderer::Init(new VL::ForwardRenderer());

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	this->_Widgets.push_back(VL::Ref<OutputWidget>(new OutputWidget()));
	this->_Widgets.push_back(VL::Ref<ViewportWidget>(new ViewportWidget()));

	this->GetModule<VL::WindowModule>()->Window->Show();
	this->GetModule<VL::WindowModule>()->Context->MakeCurrent();
}

void Editor::OnTerminate()
{

}

void Editor::OnUpdate(VL::TimeStep TS)
{
	VL::ImGuiModule::BeginFrame();

	if (VL::ImGuiModule::BeginDockSpace())
	{
		for (auto Widget : this->_Widgets)
		{
			if (Widget->IsActive)
			{
				Widget->OnUpdate(TS);
			}
		}
	}

	ImGui::End();

	VL::ImGuiModule::EndFrame();
}

void Editor::OnEvent(VL::Event* E)
{
	this->_Input.HandleEvent(E);

	if (this->_Input.IsHeld(VOLUND_KEY_TAB))
	{
		this->GetModule<VL::WindowModule>()->Window->SetCursorMode(VL::CursorMode::NORMAL);
	}
	else
	{
		this->GetModule<VL::WindowModule>()->Window->SetCursorMode(VL::CursorMode::DISABLED);
	}

	for (auto Widget : this->_Widgets)
	{
		if (Widget->IsActive)
		{
			Widget->OnEvent(E);
		}
	}
}