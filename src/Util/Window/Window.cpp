#include "Window.h"

#include "../Event/EventPublic.h"
#include "../Input/KeycodeTranslator.h"

EventDispatcher* Window::m_event_dispatcher_instance = nullptr;

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	m_width = width;
	m_height = height;
	m_title = title;

	m_window = nullptr;

	m_first_mouse = true;

	m_event_dispatcher_instance = EventDispatcher::inst();
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

bool Window::initialize(int num_samples)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, num_samples);

	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

	if (!m_window)
	{
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(m_window, Window::key_callback);
	glfwSetCursorPosCallback(m_window, Window::cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, Window::mouse_button_callback);
	glfwSetScrollCallback(m_window, Window::scroll_callback);

	return true;
}

GLFWwindow* Window::get_handle()
{
	return m_window;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		KeyPressedPayload payload;
		payload.keycode = KeycodeTranslator::inst()->convert_glfw_to_app_key_code(key);
		payload.scancode = scancode;
		payload.is_shift_pressed = mods & 1;
		payload.is_control_pressed = mods & 2;
		payload.is_alt_pressed = mods & 4;

		m_event_dispatcher_instance->publish(EventType::KeyPressed, "Window", (const void*)(&payload));
	}
	else if (action == GLFW_REPEAT)
	{
		KeyRepeatedPayload payload;
		payload.keycode = KeycodeTranslator::inst()->convert_glfw_to_app_key_code(key);
		payload.scancode = scancode;
		payload.is_shift_pressed = mods & 1;
		payload.is_control_pressed = mods & 2;
		payload.is_alt_pressed = mods & 4;

		m_event_dispatcher_instance->publish(EventType::KeyRepeated, "Window", (const void*)(&payload));
	}
	else
	{
		KeyReleasedPayload payload;
		payload.keycode = KeycodeTranslator::inst()->convert_glfw_to_app_key_code(key);
		payload.scancode = scancode;
		payload.is_shift_pressed = mods & 1;
		payload.is_control_pressed = mods & 2;
		payload.is_alt_pressed = mods & 4;

		m_event_dispatcher_instance->publish(EventType::KeyReleased, "Window", (const void*)(&payload));
	}
}

void Window::cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	MouseMovedPayload payload;
	payload.x_pos = x_pos;
	payload.y_pos = y_pos;

	m_event_dispatcher_instance->publish(EventType::MouseMoved, "Window", (const void*)(&payload));
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		MouseButtonPressedPayload payload;
		payload.button = KeycodeTranslator::inst()->convert_glfw_to_app_key_code(button);
		payload.is_shift_pressed = mods & 1;
		payload.is_control_pressed = mods & 2;
		payload.is_alt_pressed = mods & 4;

		m_event_dispatcher_instance->publish(EventType::MouseButtonPressed, "Window", (const void*)(&payload));
	}
	else // action == GLFW_RELEASE there is no repeated input for mice
	{
		MouseButtonReleasedPayload payload;
		payload.button = KeycodeTranslator::inst()->convert_glfw_to_app_key_code(button);
		payload.is_shift_pressed = mods & 1;
		payload.is_control_pressed = mods & 2;
		payload.is_alt_pressed = mods & 4;

		m_event_dispatcher_instance->publish(EventType::MouseButtonReleased, "Window", (const void*)(&payload));
	}
}

void Window::scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	MouseScrolledPayload payload;
	payload.x_offset = x_offset;
	payload.y_offset = y_offset;

	m_event_dispatcher_instance->publish(EventType::MouseScrolled, "Window", (const void*)(&payload));
}