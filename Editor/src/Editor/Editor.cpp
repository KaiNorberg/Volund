#include "PCH/PCH.h"

#include "Editor.h"

#include "EditorLayer/EditorLayer.h"
#include "UILayer/UILayer.h"

Editor::Editor()
{
	this->AttachLayer(new EditorLayer());	
	this->AttachLayer(new UILayer());	
}