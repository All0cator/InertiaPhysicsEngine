#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Util/Window/Window.h"
#include "Util/Input/InputPublic.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main()
{	
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Inertia");

	if (!window->initialize(4))
	{
		std::cout << "Error: Could not initialize Window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error: Could not initialize GLEW!" << std::endl;
		delete window;
		glfwTerminate();
		return -1;
	}

	while (!Input::inst()->is_pressed(Keycode::KEY_0))
	{

		glfwSwapBuffers(window->get_handle());
		glfwPollEvents();
	}

	return 0;
}