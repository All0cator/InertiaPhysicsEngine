#pragma once

#include "Keycodes.h"
#include <string>

class EventDispatcher;

class Input
{
public:
	static Input* inst();

	bool is_shift_pressed();
	bool is_control_pressed();
	bool is_alt_pressed();

	bool is_pressed(Keycode key);
	bool is_pressed(char key);

	double get_mouse_pos_x();
	double get_mouse_pos_y();

	double get_mouse_scroll_offset_x();
	double get_mouse_scroll_offset_y();

private:
	Input();
	~Input();

	void press_key(Keycode key);
	void release_key(Keycode key);
	void update_shift_control_alt_activations(bool is_shift_pressed, bool is_control_pressed, bool is_alt_pressed);

	bool key_pressed_callback(const std::string publisher_name, const void* p);
	bool key_repeated_callback(const std::string publisher_name, const void* p);
	bool key_released_callback(const std::string publisher_name, const void* p);
	bool mouse_moved_callback(const std::string publisher_name, const void* p);
	bool mouse_button_pressed_callback(const std::string publisher_name, const void* p);
	bool mouse_button_released_callback(const std::string publisher_name, const void* p);
	bool mouse_scrolled_callback(const std::string publisher_name, const void* p);

private:
	static Input* m_instance;
	EventDispatcher* m_event_dispatcher_instance;

	// Data updated per frame
	double m_mouse_pos_x;
	double m_mouse_pos_y;

	double m_mouse_scroll_offset_x;
	double m_mouse_scroll_offset_y;

	bool m_is_key_pressed_map[Keycode::KEY_MAX + 1];

	bool m_is_shift_pressed;
	bool m_is_control_pressed;
	bool m_is_alt_pressed;
};