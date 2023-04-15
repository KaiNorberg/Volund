#include "PCH/PCH.h"

#include "Editor.h"

#include "Widget/OutputWidget/OutputWidget.h"
#include "Widget/ViewportWidget/ViewportWidget.h"
#include "Widget/InspectorWidget/InspectorWidget.h"
#include "Widget/HierarchyWidget/HierarchyWidget.h"

#include "EditorModule/EditorModule.h"

void Editor::OnRun()
{
	this->AttachModule(new VL::WindowModule(VL::GraphicsAPI::OpenGL, std::make_shared<VL::ForwardRenderer>()));
	this->AttachModule(new VL::ImGuiModule());
	this->AttachModule(new VL::GameModule());
	this->AttachModule(new VL::AudioModule());
	this->AttachModule(new EditorModule());

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);

	this->m_Widgets.push_back(VL::Ref<OutputWidget>(new OutputWidget(this)));
	this->m_Widgets.push_back(VL::Ref<ViewportWidget>(new ViewportWidget(this)));
	this->m_Widgets.push_back(VL::Ref<InspectorWidget>(new InspectorWidget(this)));
	this->m_Widgets.push_back(VL::Ref<HierarchyWidget>(new HierarchyWidget(this)));
}

void Editor::OnTerminate()
{

}

void Editor::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VL::EventType::Render:
	{ 
		VL::ImGuiModule::BeginFrame();

		if (VL::ImGuiModule::BeginDockSpace())
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Widget"))
				{
					for (const auto& widget : this->m_Widgets)
					{
						if (ImGui::MenuItem(widget->GetName()))
						{
							widget->IsActive = true;
						}
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			for (const auto& widget : this->m_Widgets)
			{
				if (widget->IsActive)
				{
					widget->OnRender();
				}
			}
		}

		ImGui::End();

		VL::ImGuiModule::EndFrame();
	}
	break;	
	case VL::EventType::Update:
	{
		const float ts = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

		for (const auto& widget : this->m_Widgets)
		{
			if (widget->IsActive)
			{
				widget->OnUpdate(ts);
			}
		}
	}
	break;
	case VL::EventType::Key:
	{
		for (const auto& widget : this->m_Widgets)
		{
			if (widget->IsActive)
			{
				widget->OnKey(e);
			}
		}
	}
	break;
	case VL::EventType::WindowClose:
	{
		this->Terminate();
	}
	break;
	default:
	{

	}
	break;
	}
}