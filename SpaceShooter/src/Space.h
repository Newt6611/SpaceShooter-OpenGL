#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Heart.h"
#include <vector>

class Space : public GameObject
{
public:
	Space();
	~Space();
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;
	void Destroy() override { isAlive = false; }

	inline const bool IsAlive() const { return isAlive; }
	inline void TakeDamage(int i) { health -= 1; heart->InitCount(health); if (health <= 0) isAlive = false; }
	inline const void SetPositionY(float y) { this->position.y = y; }

private:
	void EadgeDetection();
private:
	glm::vec4 m_Color;
	float speed;
	bool canMove = true;

	// Health
	Heart* heart;
	int health;
	bool isAlive;
};