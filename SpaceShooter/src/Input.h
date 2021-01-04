#pragma once

#include "GLFW/glfw3.h"

class Input 
{
public:
	static bool keys[1024];
	static bool GetKeyDown(int key);
};