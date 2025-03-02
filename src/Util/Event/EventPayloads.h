#pragma once

#include "../Input/Keycodes.h"

class KeyPressedPayload
{
public:
	Keycode keycode = Keycode::KEY_INVALID;
	int scancode = -1;
	bool is_shift_pressed = false;
	bool is_control_pressed = false;
	bool is_alt_pressed = false;
};

class KeyRepeatedPayload
{
public:
	Keycode keycode = Keycode::KEY_INVALID;
	int scancode = -1;
	bool is_shift_pressed = false;
	bool is_control_pressed = false;
	bool is_alt_pressed = false;
};

class KeyReleasedPayload
{
public:
	Keycode keycode = Keycode::KEY_INVALID;
	int scancode = -1;
	bool is_shift_pressed = false;
	bool is_control_pressed = false;
	bool is_alt_pressed = false;
};

class MouseMovedPayload
{
public:
	double x_pos = -1.0;
	double y_pos = -1.0;
};

class MouseButtonPressedPayload
{
public:
	Keycode button = Keycode::KEY_INVALID;
	bool is_shift_pressed = false;
	bool is_control_pressed = false;
	bool is_alt_pressed = false;
};

class MouseButtonReleasedPayload
{
public:
	Keycode button = Keycode::KEY_INVALID;
	bool is_shift_pressed = false;
	bool is_control_pressed = false;
	bool is_alt_pressed = false;
};

class MouseScrolledPayload
{
public:
	double x_offset = 0.0f;
	double y_offset = 0.0f;
};