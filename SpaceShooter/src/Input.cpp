#include "Input.h"

bool Input::keys[1024];

bool Input::GetKeyDown(int key)
{
	return keys[key];
}