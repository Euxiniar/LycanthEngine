#include <Application.hpp>
#include <misc/object_tracker.h>
#include <conio.h>

int main()
{
	std::unique_ptr<Ly::Application> app_ptr(new Ly::Application("LycanthGame"));

	app_ptr->init();
	app_ptr->run();

#ifdef _DEBUG
	{
		app_ptr.reset();

		Anvil::ObjectTracker::get()->check_for_leaks();
	}
#endif
	_getch();
	return 0;
}