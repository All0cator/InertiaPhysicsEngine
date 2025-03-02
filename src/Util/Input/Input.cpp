#include "Input.h"

#include "../Event/EventPublic.h"

Input* Input::m_instance = nullptr;

Input* Input::inst()
{
	if (!m_instance)
	{
		m_instance = new Input();
	}

	return m_instance;
}

/*
* Returns true if at least one shift button is pressed
*/
bool Input::is_shift_pressed()
{
	return m_is_shift_pressed;
}

/*
* Returns true if at least one control button is pressed
*/
bool Input::is_control_pressed()
{
	return m_is_control_pressed;
}

/*
* Returns true is at least one alt button is pressed
*/
bool Input::is_alt_pressed()
{
	return m_is_alt_pressed;
}


bool Input::is_pressed(Keycode key)
{
	return m_is_key_pressed_map[key];
}

bool Input::is_pressed(char key)
{
	if (key > Keycode::KEY_MAX)
		return false;

	// Convert to uppercase look at ASCII table to understand difference between lowercase and uppercase
	if (key > 'a' - 1 && key < 'z' + 1)
	{
		key -= 32;
	}

	return m_is_key_pressed_map[key];
}

double Input::get_mouse_pos_x()
{
	return m_mouse_pos_x;
}

double Input::get_mouse_pos_y()
{
	return m_mouse_pos_y;
}

double Input::get_mouse_scroll_offset_x()
{
	return m_mouse_scroll_offset_x;
}

double Input::get_mouse_scroll_offset_y()
{
	return m_mouse_scroll_offset_y;
}

Input::Input()
{
	m_event_dispatcher_instance = EventDispatcher::inst();

	m_event_dispatcher_instance->subscribe(EventType::KeyPressed, "Input", GET_FUNCTION_POINTER(Input::key_pressed_callback, this));
	m_event_dispatcher_instance->subscribe(EventType::KeyRepeated, "Input", GET_FUNCTION_POINTER(Input::key_repeated_callback, this));
	m_event_dispatcher_instance->subscribe(EventType::KeyReleased, "Input", GET_FUNCTION_POINTER(Input::key_released_callback, this));
	m_event_dispatcher_instance->subscribe(EventType::MouseMoved, "Input", GET_FUNCTION_POINTER(Input::mouse_moved_callback, this));
	m_event_dispatcher_instance->subscribe(EventType::MouseButtonPressed, "Input", GET_FUNCTION_POINTER(Input::mouse_button_pressed_callback, this));
	m_event_dispatcher_instance->subscribe(EventType::MouseButtonReleased, "Input", GET_FUNCTION_POINTER(Input::mouse_button_released_callback, this));
	m_event_dispatcher_instance->subscribe(EventType::MouseScrolled, "Input", GET_FUNCTION_POINTER(Input::mouse_scrolled_callback, this));

	m_is_shift_pressed = false;
	m_is_control_pressed = false;
	m_is_alt_pressed = false;

	for (int i = 0; i < Keycode::KEY_MAX + 1; ++i)
	{
		m_is_key_pressed_map[i] = false;
	}

	m_mouse_pos_x = 0.0;
	m_mouse_pos_y = 0.0;
	m_mouse_scroll_offset_x = 0.0;
	m_mouse_scroll_offset_y = 0.0;
}

Input::~Input()
{

}

void Input::press_key(Keycode key)
{
	m_is_key_pressed_map[key] = true;
}

void Input::release_key(Keycode key)
{
	m_is_key_pressed_map[key] = false;
}

void Input::update_shift_control_alt_activations(bool is_shift_pressed, bool is_control_pressed, bool is_alt_pressed)
{
	m_is_shift_pressed = is_shift_pressed;
	m_is_control_pressed = is_control_pressed;
	m_is_alt_pressed = is_alt_pressed;
}

bool Input::key_pressed_callback(const std::string publisher_name, const void* p)
{
	const KeyPressedPayload* payload = (const KeyPressedPayload*)(p);

	press_key(payload->keycode);

	update_shift_control_alt_activations(payload->is_shift_pressed, payload->is_control_pressed, payload->is_alt_pressed);

	return true;
}

bool Input::key_repeated_callback(const std::string publisher_name, const void* p)
{
	const KeyRepeatedPayload* payload = (const KeyRepeatedPayload*)(p);

	press_key(payload->keycode);

	update_shift_control_alt_activations(payload->is_shift_pressed, payload->is_control_pressed, payload->is_alt_pressed);

	return true;
}

bool Input::key_released_callback(const std::string publisher_name, const void* p)
{
	const KeyReleasedPayload* payload = (const KeyReleasedPayload*)(p);

	release_key(payload->keycode);

	update_shift_control_alt_activations(payload->is_shift_pressed, payload->is_control_pressed, payload->is_alt_pressed);

	return true;
}

bool Input::mouse_moved_callback(const std::string publisher_name, const void* p)
{
	const MouseMovedPayload* payload = (const MouseMovedPayload*)(p);

	m_mouse_pos_x = payload->x_pos;
	m_mouse_pos_y = payload->y_pos;

	return true;
}

bool Input::mouse_button_pressed_callback(const std::string publisher_name, const void* p)
{
	const MouseButtonPressedPayload* payload = (const MouseButtonPressedPayload*)(p);

	press_key(payload->button);

	update_shift_control_alt_activations(payload->is_shift_pressed, payload->is_control_pressed, payload->is_alt_pressed);

	return true;
}

bool Input::mouse_button_released_callback(const std::string publisher_name, const void* p)
{
	const MouseButtonReleasedPayload* payload = (const MouseButtonReleasedPayload*)(p);

	release_key(payload->button);

	update_shift_control_alt_activations(payload->is_shift_pressed, payload->is_control_pressed, payload->is_alt_pressed);

	return true;
}

bool Input::mouse_scrolled_callback(const std::string publisher_name, const void* p)
{
	const MouseScrolledPayload* payload = (const MouseScrolledPayload*)(p);

	m_mouse_scroll_offset_x = payload->x_offset;
	m_mouse_scroll_offset_y = payload->y_offset;

	return true;
}