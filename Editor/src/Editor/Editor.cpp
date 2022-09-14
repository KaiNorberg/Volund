#include "PCH/PCH.h"

#include "Editor.h"

#include "EditorLayer/EditorLayer.h"

Editor::Editor()
{
	this->AttachLayer(new EditorLayer());
}