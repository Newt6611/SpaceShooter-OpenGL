#pragma once

#include "GameObject.h"

class HealthBar : public GameObject
{
public:
	HealthBar();
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;

	inline const float GetScaleX() { return this->scale.x; }
	inline const void SetScaleX(float x) { this->scale.x = x; }
	inline const void DecreaseX(float x) { this->scale.x -= x; }
	inline const void SetColor(glm::vec4 color) { this->m_color = color; }
	inline const void SetPositoin(glm::vec3 position) { this->position = position; }
	inline const void SetAlive(bool alive) { isAlive = alive; }
	inline void Destroy() override { isAlive = false; }
private:
	bool isAlive = false;
	glm::vec4 m_color;
};