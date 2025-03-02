#pragma once

#include "Input.h"

/*
* USAGE EXAMPLE
*/

/*
#include <iostream>

#include "Input/InputPublic.h"
#include "Window/Window.h"

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Error: Could not initialize GLFW!" << std::endl;
		return -1;
	}

	Window w(500, 500, "Lol123");

	if (!w.initialize())
	{
		std::cout << "Error: Could not initialize Window!" << std::endl;
		return -1;
	}



	while (!Input::inst()->is_pressed('0'))
	{
		glfwPollEvents();

		if (Input::inst()->is_alt_pressed())
		{
			std::cout << "Mouse Position (x, y): (" << Input::inst()->get_mouse_pos_x() << ", " << Input::inst()->get_mouse_pos_y() << ")" << std::endl;
		}

		if (Input::inst()->is_pressed(Keycode::KEY_LEFT_SHIFT) && Input::inst()->is_pressed('A'))
		{
			std::cout << "Mouse Scroll Offset (sx, sy): (" << Input::inst()->get_mouse_scroll_offset_x() << ", " << Input::inst()->get_mouse_scroll_offset_y() << ")" << std::endl;
		}
	}

	return 0;
}
*/