#include "PCH/PCH.h"

#include "EditorLayer.h"

#include "VML/VML.h"

#include <windows.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void EditorLayer::OnAttach()
{
	auto NewAPI = RenderingAPI::Create(RenderingAPI::API::OPENGL);

	auto NewEventDispatcher = Ref<EventDispatcher>(new EventDispatcher(this));
	this->_Window = Ref<Window>(new Window(NewEventDispatcher, 500, 500, false));

	this->_Window->SetTitle("Volund Editor");
	this->_Window->SetCursorMode("Normal");
	this->_Window->SetFocus();
	this->_Window->SetProcedureCatch((Volund::ProcCatch)ImGui_ImplWin32_WndProcHandler);

	this->_Context = Context::Create(this->_Window);
	this->_Context->SetVSync(true);
	this->_Context->MakeCurrent();

	Renderer::Init(NewAPI);

	this->_Scene = Scene::Deserialize("Test.scene");

	IMGUI_CHECKVERSION();    
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;    
	
	ImGui_ImplWin32_Init(this->_Window->GetHandle());
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
}

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(TimeStep TS)
{
	this->_Context->MakeCurrent();

	Camera* ActiveCamera = Camera::GetActiveCamera(this->_Scene);

	if (ActiveCamera != nullptr)
	{
		Mat4x4 ViewProjMatrix = ActiveCamera->GetProjectionMatrix(this->_Context->GetWindow()->GetAspectRatio()) * ActiveCamera->GetViewMatrix();
		Vec3 EyePosition = ActiveCamera->GetEntity()->GetComponent<Transform>()->Position;
		auto& PointLights = this->_Scene->ComponentView<PointLight>();

		Renderer::BeginScene(ViewProjMatrix, EyePosition, PointLights);

		if (_Scene != nullptr)
		{
			this->_Scene->OnUpdate(TS);
		}
	
		Renderer::EndScene(this->_Context);
	}
	else
	{
		if (_Scene != nullptr)
		{
			this->_Scene->OnUpdate(TS);
		}
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	this->_Context->Flush();

	this->_Window->Update();
}

void EditorLayer::OnEvent(Event* E)
{
	switch (E->GetType())
	{
	case EventType::WINDOW_CLOSE:
	{
		this->GetApp()->Terminate();
	}
	break;
	}

	if (this->_Scene != nullptr)
	{
		this->_Scene->OnEvent(E);
	}
}
