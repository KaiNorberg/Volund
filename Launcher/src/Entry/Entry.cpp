#include "PCH/PCH.h"

#include "Launcher/Launcher.h"

VL::Ref<VL::Application> Volund::Entry()
{
	return VL::Ref<Launcher>(new Launcher());
}