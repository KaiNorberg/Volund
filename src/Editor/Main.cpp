#include "Editor.h"

#include <Volund.h>

int main()
{
	VOLUND_PROFILE_FUNCTION();

	auto app = std::shared_ptr<Editor>(new Editor());

	app->Run();

	return EXIT_SUCCESS;
}
