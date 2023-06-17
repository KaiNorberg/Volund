#include "PCH/PCH.h"
#include "Launcher.h"

void Launcher::Procedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_WINDOW_CLOSE:
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
