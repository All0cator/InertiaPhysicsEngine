#pragma once


#include <GLFW/glfw3.h>

class EventDispatcher;

class Window
{
public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	// Prohibit usage of assignment, copy, move constructors 
	Window& operator=(const Window& other) = delete;
	Window(const Window& other) = delete;
	Window(Window&& other) = delete;

	bool initialize(int num_samples = 1);

	GLFWwindow* get_handle();

private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

private:
	static EventDispatcher* m_event_dispatcher_instance;

	GLFWwindow* m_window;
	bool m_first_mouse;
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;
};