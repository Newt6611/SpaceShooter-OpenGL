#pragma once

#include "GameObject.h"
#include "HealthBar.h"

class LittleEnemy : public GameObject
{
public:
	LittleEnemy();
	~LittleEnemy();
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;
	void Spaw(glm::vec3 spawnPosition);
	
	void TakeDamage(int i);
	
	inline bool const IsAlive() const { return isAlive; }
	inline void Destroy() override;

private:
	int max_health;
	int health;
	bool isAlive = false;
	float speed = 200.f;
	int adjust_health_bar = 0;
	HealthBar* bar;
};