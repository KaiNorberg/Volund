#include "PCH/PCH.h"
#include "Launcher.h"

void Launcher::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VL::EventType::WindowClose:
	{
		this->Terminate();
	}
	break;
	}
}

Launcher::Launcher()
{
	this->AttachModule(new VL::WindowModule());
	this->AttachModule(new VL::GameModule());
	this->AttachModule(new VL::AudioModule());
	
	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);
	VL::Renderer::Init(std::make_shared<VL::ForwardRenderer>());

	this->GetModule<VL::GameModule>()->LoadNewScene(MAIN_SCENE);
}
