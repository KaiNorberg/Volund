#include "Editor/Editor.h"

#include <Volund.h>

int main()
{
	VOLUND_PROFILE_FUNCTION();

	auto app = VL::Ref<Editor>(new Editor());

	app->Run();

	return EXIT_SUCCESS;
}
