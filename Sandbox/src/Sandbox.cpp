#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "GameApplication.h"

int main()
{
	GameApplication app;
	Logger::Trace("{}", 2);
	app.run();

	return 0;
}