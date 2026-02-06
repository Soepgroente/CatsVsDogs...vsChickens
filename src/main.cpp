#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "Camera.hpp"
#include "InputHandler.hpp"
#include "Config.hpp"
#include "CatsVsDogs.hpp"

int	main()
{
	rts::CatsVsDogs	app;
	
	if (app.initialize() == false)
	{
		std::cerr << "Failed to initialize application" << std::endl;
		return 1;
	}

	app.run();
	app.shutdown();
	
	return 0;
}
