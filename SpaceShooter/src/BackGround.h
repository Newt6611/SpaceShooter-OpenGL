#pragma once

#include "GameObject.h"

class BackGround : public GameObject
{
public :
	BackGround();
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;

private:
	glm::mat4 view;
	float speed;
	glm::vec3 second_position;
};