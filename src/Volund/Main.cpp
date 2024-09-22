#include "Application/Application.h"

namespace Volund
{
    std::shared_ptr<Application> Entry();
}

int main(int argc, char** argv)
{
    VOLUND_PROFILE_FUNCTION();

	auto app = Volund::Entry();

	app->Run();

	return EXIT_SUCCESS;
}
