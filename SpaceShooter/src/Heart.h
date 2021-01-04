#pragma once
#include "GameObject.h"

class Heart : public GameObject
{
public:
	Heart() {}
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;

	inline void const InitCount(int i) { this->count = i; }
	inline void const SetColor(glm::vec4 color) { this->m_Color = color; }
private:
	int count;
	glm::vec4 m_Color;
};