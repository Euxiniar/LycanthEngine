#include <App.h>

int main()
{
	std::unique_ptr<App> app_ptr(new App());

	app_ptr->init();
	app_ptr->run();

#ifdef _DEBUG
	{
		app_ptr.reset();

		Anvil::ObjectTracker::get()->check_for_leaks();
	}
#endif
	return 0;
}