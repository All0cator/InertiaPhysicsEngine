#pragma once

/*
* Application key codes are based on the ASCII character representations of the keys
* eg KEY_A = 41 and 'A' = 41 so we can do Input::IsPressed('A') and Input::IsPressed(KEY_A)
* keys codes that do not have an ASCII representation can only be queried by their key code
* eg KEY_SHIFT shift does not have an ASCII representation the same with mouse buttons etc...
*/

// Application Key codes
enum Keycode : unsigned int
{
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_LEFT_SHIFT,
	KEY_LEFT_CONTROL,
	KEY_LEFT_ALT,
	KEY_LEFT_SUPER,
	KEY_RIGHT_SHIFT,
	KEY_RIGHT_CONTROL,
	KEY_RIGHT_ALT,
	KEY_RIGHT_SUPER,
	KEY_MENU,
	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_DECIMAL,
	KEY_SPACE, // 32
	KEY_RIGHT,
	KEY_LEFT,
	KEY_DOWN,
	KEY_UP,
	KEY_ESCAPE,
	KEY_ENTER,
	KEY_APOSTROPHE, // '
	KEY_TAB,
	KEY_BACKSPACE,
	KEY_INSERT,
	KEY_DELETE,
	KEY_COMMA,
	KEY_MINUS,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_PAGE_UP,
	KEY_SEMICOLON,
	KEY_PAGE_DOWN,
	KEY_EQUAL,
	KEY_HOME,
	KEY_END,
	KEY_CAPS_LOCK,
	KEY_A,// 65
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,// 90
	KEY_LEFT_BRACKET,
	KEY_BACKSLASH,
	KEY_RIGHT_BRACKET,
	KEY_NUM_LOCK,
	KEY_PRINT_SCREEN,
	KEY_TILDE, // Grave accent `
	KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT,
	KEY_KP_ADD,
	KEY_KP_ENTER,
	KEY_KP_EQUAL,
	KEY_KP_DIVIDE,
	KEY_MOUSE_LEFT,
	KEY_MOUSE_RIGHT,
	KEY_MOUSE_MIDDLE,
	KEY_INVALID,
	KEY_MAX // not used specifies size of enum
};