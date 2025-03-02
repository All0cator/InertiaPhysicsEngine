#pragma once

#include <unordered_map>
#include "Keycodes.h"
#include "GLFW/glfw3.h"

class KeycodeTranslator
{
public:
	static KeycodeTranslator* inst();
	Keycode convert_glfw_to_app_key_code(int glfw_key_code);
private:
	KeycodeTranslator();
	~KeycodeTranslator();
private:
	static KeycodeTranslator* m_instance;
	std::unordered_map<int, Keycode> m_glfw_to_app_key_code;
};