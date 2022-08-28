#include "PCH/PCH.h"

#include "Editor.h"

class TestScene : public Volund::Scene
{
public:

	void OnUpdate(Volund::TimeStep TS) override
	{

	}
};

Editor::Editor()
{
	Volund::GameLayer* NewLayer = new Volund::GameLayer();
	this->AttachLayer(NewLayer);
	NewLayer->LoadScene<TestScene>();
}


Volund::Application* Volund::CreateApplication()
{
	return new Editor();
}