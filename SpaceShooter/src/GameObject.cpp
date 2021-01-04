#include "GameObject.h"

GameObject::GameObject()
	: position(0), rotation(0), scale(0)
{}

void GameObject::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
}

