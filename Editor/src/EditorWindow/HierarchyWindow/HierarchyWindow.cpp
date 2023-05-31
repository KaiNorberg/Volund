#include "PCH/PCH.h"
#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Hierarchy");

	this->m_Context = context;

	//Add entity button and search

	this->m_EntityHierarchy = VL::Ref<EntityHierarchy>(new EntityHierarchy(this->m_Context));
	this->PushObject(this->m_EntityHierarchy);
}