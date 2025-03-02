#include "KeycodeTranslator.h"

KeycodeTranslator * KeycodeTranslator::m_instance = nullptr;

KeycodeTranslator* KeycodeTranslator::inst()
{
	if (!m_instance)
	{
		m_instance = new KeycodeTranslator();
	}

	return m_instance;
}

KeycodeTranslator::KeycodeTranslator()
{
	m_glfw_to_app_key_code =
	{
		{GLFW_MOUSE_BUTTON_1, Keycode::KEY_MOUSE_LEFT},
		{GLFW_MOUSE_BUTTON_2, Keycode::KEY_MOUSE_RIGHT},
		{GLFW_MOUSE_BUTTON_3, Keycode::KEY_MOUSE_MIDDLE},
		{GLFW_MOUSE_BUTTON_4, Keycode::KEY_INVALID},
		{GLFW_MOUSE_BUTTON_5, Keycode::KEY_INVALID},
		{GLFW_MOUSE_BUTTON_6, Keycode::KEY_INVALID},
		{GLFW_MOUSE_BUTTON_7, Keycode::KEY_INVALID},
		{GLFW_MOUSE_BUTTON_8, Keycode::KEY_INVALID},
		{GLFW_MOUSE_BUTTON_LAST, m_glfw_to_app_key_code[GLFW_MOUSE_BUTTON_8]}, // same as mouse button 8
		{GLFW_MOUSE_BUTTON_LEFT, m_glfw_to_app_key_code[GLFW_MOUSE_BUTTON_1]}, // same as mouse button 1
		{GLFW_MOUSE_BUTTON_RIGHT, m_glfw_to_app_key_code[GLFW_MOUSE_BUTTON_2]}, // same as mouse button 2
		{GLFW_MOUSE_BUTTON_MIDDLE, m_glfw_to_app_key_code[GLFW_MOUSE_BUTTON_3]}, // same as mouse button 3
		{GLFW_KEY_SPACE, Keycode::KEY_SPACE},
		{GLFW_KEY_APOSTROPHE, Keycode::KEY_APOSTROPHE},
		{GLFW_KEY_COMMA, Keycode::KEY_COMMA},
		{GLFW_KEY_MINUS, Keycode::KEY_MINUS},
		{GLFW_KEY_PERIOD, Keycode::KEY_PERIOD},
		{GLFW_KEY_SLASH, Keycode::KEY_SLASH},
		{GLFW_KEY_0, Keycode::KEY_0},
		{GLFW_KEY_1, Keycode::KEY_1},
		{GLFW_KEY_2, Keycode::KEY_2},
		{GLFW_KEY_3, Keycode::KEY_3},
		{GLFW_KEY_4, Keycode::KEY_4},
		{GLFW_KEY_5, Keycode::KEY_5},
		{GLFW_KEY_6, Keycode::KEY_6},
		{GLFW_KEY_7, Keycode::KEY_7},
		{GLFW_KEY_8, Keycode::KEY_8},
		{GLFW_KEY_9, Keycode::KEY_9},
		{GLFW_KEY_SEMICOLON, Keycode::KEY_SEMICOLON},
		{GLFW_KEY_EQUAL, Keycode::KEY_EQUAL},
		{GLFW_KEY_A, Keycode::KEY_A},
		{GLFW_KEY_B, Keycode::KEY_B},
		{GLFW_KEY_C, Keycode::KEY_C},
		{GLFW_KEY_D, Keycode::KEY_D},
		{GLFW_KEY_E, Keycode::KEY_E},
		{GLFW_KEY_F, Keycode::KEY_F},
		{GLFW_KEY_G, Keycode::KEY_G},
		{GLFW_KEY_H, Keycode::KEY_H},
		{GLFW_KEY_I, Keycode::KEY_I},
		{GLFW_KEY_J, Keycode::KEY_J},
		{GLFW_KEY_K, Keycode::KEY_K},
		{GLFW_KEY_L, Keycode::KEY_L},
		{GLFW_KEY_M, Keycode::KEY_M},
		{GLFW_KEY_N, Keycode::KEY_N},
		{GLFW_KEY_O, Keycode::KEY_O},
		{GLFW_KEY_P, Keycode::KEY_P},
		{GLFW_KEY_Q, Keycode::KEY_Q},
		{GLFW_KEY_R, Keycode::KEY_R},
		{GLFW_KEY_S, Keycode::KEY_S},
		{GLFW_KEY_T, Keycode::KEY_T},
		{GLFW_KEY_U, Keycode::KEY_U},
		{GLFW_KEY_V, Keycode::KEY_V},
		{GLFW_KEY_W, Keycode::KEY_W},
		{GLFW_KEY_X, Keycode::KEY_X},
		{GLFW_KEY_Y, Keycode::KEY_Y},
		{GLFW_KEY_Z, Keycode::KEY_Z},
		{GLFW_KEY_LEFT_BRACKET, Keycode::KEY_LEFT_BRACKET},
		{GLFW_KEY_BACKSLASH, Keycode::KEY_BACKSLASH},
		{GLFW_KEY_RIGHT_BRACKET, Keycode::KEY_RIGHT_BRACKET},
		{GLFW_KEY_GRAVE_ACCENT, Keycode::KEY_TILDE},
		{GLFW_KEY_WORLD_1, Keycode::KEY_INVALID},
		{GLFW_KEY_WORLD_2, Keycode::KEY_INVALID},
		{GLFW_KEY_ESCAPE, Keycode::KEY_ESCAPE},
		{GLFW_KEY_ENTER, Keycode::KEY_ENTER},
		{GLFW_KEY_TAB, Keycode::KEY_TAB},
		{GLFW_KEY_BACKSPACE, Keycode::KEY_BACKSPACE},
		{GLFW_KEY_INSERT, Keycode::KEY_INSERT},
		{GLFW_KEY_DELETE, Keycode::KEY_DELETE},
		{GLFW_KEY_RIGHT, Keycode::KEY_RIGHT},
		{GLFW_KEY_LEFT, Keycode::KEY_LEFT},
		{GLFW_KEY_DOWN, Keycode::KEY_DOWN},
		{GLFW_KEY_UP, Keycode::KEY_UP},
		{GLFW_KEY_PAGE_UP, Keycode::KEY_PAGE_UP},
		{GLFW_KEY_PAGE_DOWN, Keycode::KEY_PAGE_DOWN},
		{GLFW_KEY_HOME, Keycode::KEY_HOME},
		{GLFW_KEY_END, Keycode::KEY_END},
		{GLFW_KEY_CAPS_LOCK, Keycode::KEY_CAPS_LOCK},
		{GLFW_KEY_SCROLL_LOCK, Keycode::KEY_INVALID},
		{GLFW_KEY_NUM_LOCK, Keycode::KEY_NUM_LOCK},
		{GLFW_KEY_PRINT_SCREEN, Keycode::KEY_PRINT_SCREEN},
		{GLFW_KEY_PAUSE, Keycode::KEY_INVALID},
		{GLFW_KEY_F1, Keycode::KEY_F1},
		{GLFW_KEY_F2, Keycode::KEY_F2},
		{GLFW_KEY_F3, Keycode::KEY_F3},
		{GLFW_KEY_F4, Keycode::KEY_F4},
		{GLFW_KEY_F5, Keycode::KEY_F5},
		{GLFW_KEY_F6, Keycode::KEY_F6},
		{GLFW_KEY_F7, Keycode::KEY_F7},
		{GLFW_KEY_F8, Keycode::KEY_F8},
		{GLFW_KEY_F9, Keycode::KEY_F9},
		{GLFW_KEY_F10, Keycode::KEY_F10},
		{GLFW_KEY_F11, Keycode::KEY_F11},
		{GLFW_KEY_F12, Keycode::KEY_F12},
		{GLFW_KEY_F13, Keycode::KEY_INVALID},
		{GLFW_KEY_F14, Keycode::KEY_INVALID},
		{GLFW_KEY_F15, Keycode::KEY_INVALID},
		{GLFW_KEY_F16, Keycode::KEY_INVALID},
		{GLFW_KEY_F17, Keycode::KEY_INVALID},
		{GLFW_KEY_F18, Keycode::KEY_INVALID},
		{GLFW_KEY_F19, Keycode::KEY_INVALID},
		{GLFW_KEY_F20, Keycode::KEY_INVALID},
		{GLFW_KEY_F21, Keycode::KEY_INVALID},
		{GLFW_KEY_F22, Keycode::KEY_INVALID},
		{GLFW_KEY_F23, Keycode::KEY_INVALID},
		{GLFW_KEY_F24, Keycode::KEY_INVALID},
		{GLFW_KEY_F25, Keycode::KEY_INVALID},
		{GLFW_KEY_KP_0, Keycode::KEY_KP_0},
		{GLFW_KEY_KP_1, Keycode::KEY_KP_1},
		{GLFW_KEY_KP_2, Keycode::KEY_KP_2},
		{GLFW_KEY_KP_3, Keycode::KEY_KP_3},
		{GLFW_KEY_KP_4, Keycode::KEY_KP_4},
		{GLFW_KEY_KP_5, Keycode::KEY_KP_5},
		{GLFW_KEY_KP_6, Keycode::KEY_KP_6},
		{GLFW_KEY_KP_7, Keycode::KEY_KP_7},
		{GLFW_KEY_KP_8, Keycode::KEY_KP_8},
		{GLFW_KEY_KP_9, Keycode::KEY_KP_9},
		{GLFW_KEY_KP_DECIMAL, Keycode::KEY_KP_DECIMAL},
		{GLFW_KEY_KP_DIVIDE, Keycode::KEY_KP_DIVIDE},
		{GLFW_KEY_KP_MULTIPLY, Keycode::KEY_KP_MULTIPLY},
		{GLFW_KEY_KP_SUBTRACT, Keycode::KEY_KP_SUBTRACT},
		{GLFW_KEY_KP_ADD, Keycode::KEY_KP_ADD},
		{GLFW_KEY_KP_ENTER, Keycode::KEY_KP_ENTER},
		{GLFW_KEY_KP_EQUAL, Keycode::KEY_KP_EQUAL},
		{GLFW_KEY_LEFT_SHIFT, Keycode::KEY_LEFT_SHIFT},
		{GLFW_KEY_LEFT_CONTROL, Keycode::KEY_LEFT_CONTROL},
		{GLFW_KEY_LEFT_ALT, Keycode::KEY_LEFT_ALT},
		{GLFW_KEY_LEFT_SUPER, Keycode::KEY_LEFT_SUPER},
		{GLFW_KEY_RIGHT_SHIFT, Keycode::KEY_RIGHT_SHIFT},
		{GLFW_KEY_RIGHT_CONTROL, Keycode::KEY_RIGHT_CONTROL},
		{GLFW_KEY_RIGHT_ALT, Keycode::KEY_RIGHT_ALT},
		{GLFW_KEY_RIGHT_SUPER, Keycode::KEY_RIGHT_SUPER},
		{GLFW_KEY_MENU, Keycode::KEY_MENU},
		{GLFW_KEY_LAST, m_glfw_to_app_key_code[GLFW_KEY_MENU]} // same as key menu
	};
}

KeycodeTranslator::~KeycodeTranslator()
{
}


Keycode KeycodeTranslator::convert_glfw_to_app_key_code(int glfw_key_code)
{
	return m_glfw_to_app_key_code[glfw_key_code];
}