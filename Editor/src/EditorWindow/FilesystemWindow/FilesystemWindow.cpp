#include "PCH/PCH.h"

#include "FilesystemWindow.h"

#include "FilesystemExplorer/FilesystemExplorer.h"

FilesystemWindow::FilesystemWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Filesystem");

	this->m_Context = context;

	this->PushObject(new FilesystemExplorer(this->m_Context));
}
