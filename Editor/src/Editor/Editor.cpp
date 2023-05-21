#include "PCH/PCH.h"

#include "Editor.h"

#include "Widget/OutputWidget/OutputWidget.h"
#include "Widget/ViewportWidget/ViewportWidget.h"
#include "Widget/InspectorWidget/InspectorWidget.h"
#include "Widget/HierarchyWidget/HierarchyWidget.h"

#include "EditorContext/EditorContext.h"

class TestWindow : public VL::ImGuiWindow
{
public:

	const char* GetName() override
	{
		return "TestWindow"; 
	}

	TestWindow()
	{
		this->Position = VL::Vec2(500, 500);
		this->Size = VL::Vec2(500, 500);

		this->AddObject(std::make_shared<VL::ImGuiText>("Hello, World!"));
	}

private:
};

void Editor::OnRun()
{
	this->AttachModule(new VL::WindowModule(VL::GraphicsAPI::OpenGL, std::make_shared<VL::ForwardRenderer>()));
	this->AttachModule(new VL::ImGuiModule());
	this->AttachModule(new VL::AudioModule());

	auto window = this->GetModule<VL::WindowModule>()->GetWindow();
	this->m_Context = std::make_shared<EditorContext>(window);

	this->m_Widgets.push_back(VL::Ref<OutputWidget>(new OutputWidget(this->m_Context)));
	this->m_Widgets.push_back(VL::Ref<ViewportWidget>(new ViewportWidget(this->m_Context)));
	this->m_Widgets.push_back(VL::Ref<InspectorWidget>(new InspectorWidget(this->m_Context)));
	this->m_Widgets.push_back(VL::Ref<HierarchyWidget>(new HierarchyWidget(this->m_Context)));

	this->GetModule<VL::ImGuiModule>()->AddWindow(VL::Ref<TestWindow>(new TestWindow()));

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("data/fonts/OpenSans-Regular.ttf", 18.0f);
}

void Editor::OnTerminate()
{

}

void Editor::Procedure(const VL::Event& e)
{
	VOLUND_PROFILE_FUNCTION();

	if (this->m_Context->m_State != nullptr)
	{
		this->m_Context->m_State->Procedure(e);
	}

	this->m_Input.Procedure(e);

	switch (e.Type)
	{
	case VL::EventType::Render:
	{ 	
		auto window = this->m_Context->GetWindow();

		/*VL::ImGuiModule::BeginFrame();

		if (VL::ImGuiModule::BeginDockSpace())
		{
			//TODO: Improve readability of menu bar code
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::BeginMenu("Load"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + E"))
						{
							const std::string filepath = VL::Dialog::OpenFile(window);
							if (!filepath.empty())
							{
								this->m_Context->LoadNewScene(filepath);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Save"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + S"))
						{
							this->m_Context->SaveScene(this->m_Context->GetSceneFilepath());
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Save As"))
					{
						if (ImGui::MenuItem("Scene"))
						{
							const std::string filepath = VL::Dialog::OpenFile(window);
							if (!filepath.empty())
							{
								this->m_Context->SaveScene(filepath);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Reload"))
					{
						if (ImGui::MenuItem("Scene", "Ctrl + R"))
						{
							this->m_Context->LoadNewScene(this->m_Context->GetSceneFilepath());
						}

						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}

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
					widget->Procedure(e);
				}
			}
		}

		ImGui::End();

		VL::ImGuiModule::EndFrame();*/

		return;
	}
	break;	
	case VL::EventType::Key:
	{	
		auto window = this->m_Context->GetWindow();

		if (this->m_Input.IsHeld(VOLUND_KEY_CONTROL))
		{
			if (this->m_Input.IsPressed('R'))
			{
				const auto scene = this->m_Context->GetScene();
				if (scene != nullptr)
				{
					this->m_Context->LoadNewScene(this->m_Context->GetSceneFilepath());
				}
			}
			else if (this->m_Input.IsPressed('E'))
			{
				const std::string filepath = VL::Dialog::OpenFile(window);
				if (!filepath.empty())
				{
					this->m_Context->LoadNewScene(filepath);
				}
			}
			else if (this->m_Input.IsPressed('S'))
			{
				this->m_Context->SaveScene(this->m_Context->GetSceneFilepath());
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

	for (const auto& widget : this->m_Widgets)
	{
		if (widget->IsActive)
		{
			widget->Procedure(e);
		}
	}
}