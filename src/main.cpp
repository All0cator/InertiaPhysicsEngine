#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Util/Window/Window.h"
#include "Util/Camera/Camera.h"
#include "Util/Input/InputPublic.h"

#include "Util/Renderer/Renderer.h";

Window* window = nullptr;
Camera* camera = nullptr;

int cursor_capture_mode = GLFW_CURSOR_DISABLED;

float last_time = 0.0f;
float current_time = 0.0f;
float delta_time = 0.0f;

double x_pos;
double y_pos;

float x_offset;
float y_offset;
float x_last;
float y_last;
bool is_first_mouse = true;

const float sensitivity = 0.1f;

Input* input = nullptr;

void handle_input()
{
	if (input->is_pressed(Keycode::KEY_ESCAPE))
	{
		if (cursor_capture_mode == GLFW_CURSOR_DISABLED)
		{
			cursor_capture_mode = GLFW_CURSOR_NORMAL;
		}
		else
		{
			cursor_capture_mode = GLFW_CURSOR_DISABLED;
		}

		glfwSetInputMode(window->get_handle(), GLFW_CURSOR, cursor_capture_mode);
	}

	if (cursor_capture_mode == GLFW_CURSOR_NORMAL) return;

	// TRANSLATION
	// Left
	if (input->is_pressed(Keycode::KEY_A))
	{
		camera->move_left(delta_time);
	}

	// Front
	if (input->is_pressed(Keycode::KEY_W))
	{
		camera->move_forward(delta_time);
	}

	// Right
	if (input->is_pressed(Keycode::KEY_D))
	{
		camera->move_right(delta_time);
	}

	// Back
	if (input->is_pressed(Keycode::KEY_S))
	{
		camera->move_backwards(delta_time);
	}

	// Up
	if (input->is_pressed(Keycode::KEY_SPACE))
	{
		camera->move_up(delta_time);
	}

	// Down
	if (input->is_pressed(Keycode::KEY_LEFT_CONTROL))
	{
		camera->move_down(delta_time);
	}

	// ROTATION

	x_pos = input->get_mouse_pos_x();
	y_pos = input->get_mouse_pos_y();

	if (is_first_mouse)
	{
		x_last = (float)x_pos;
		y_last = (float)y_pos;
		is_first_mouse = false;
	}

	x_offset = (float)x_pos - x_last;
	y_offset = y_last - (float)y_pos;

	x_last = (float)x_pos;
	y_last = (float)y_pos;

	x_offset *= sensitivity;
	y_offset *= sensitivity;

	camera->rotate_horizontally(x_offset);
	camera->rotate_vertically(y_offset);

	camera->calculate_direction();

	// ZOOM

	camera->calculate_zoom((float)input->get_mouse_scroll_offset_y());


	if (input->is_pressed(Keycode::KEY_0))
	{
		glfwSetWindowShouldClose(window->get_handle(), GLFW_TRUE);
	}
}

int main()
{	
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Inertia");

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

	camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	input = Input::inst();

	Renderer* renderer = Renderer::inst();

	while (!glfwWindowShouldClose(window->get_handle()))
	{
		current_time = (float)glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;

		renderer->render(camera);

		handle_input();
		glfwSwapBuffers(window->get_handle());
		glfwPollEvents();
	}

	delete camera;
	delete window;

	glfwTerminate();

	return 0;
}