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

	VL::RenderingAPI::Init(VL::GraphicsAPI::OpenGL);

	this->AttachModule(new VL::GameModule());
	this->AttachModule(new VL::AudioModule());
	
	this->GetModule<VL::GameModule>()->LoadScene(MAIN_SCENE);
}
