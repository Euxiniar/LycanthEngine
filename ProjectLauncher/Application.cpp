#include <Renderer.h>
#include <stdexcept>
#include <iostream>

int main()
{
	{
		Ly::Renderer renderer;

		try {
			renderer.run();
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
	getchar();
	return 0;
}
