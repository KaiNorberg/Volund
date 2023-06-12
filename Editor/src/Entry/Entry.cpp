#include "PCH/PCH.h"

#include "Editor/Editor.h"

VL::Ref<VL::Application> Volund::Entry()
{
	return VL::Ref<Editor>(new Editor());
}