#pragma once

#include "GameObject.h"

class Bullet : GameObject
{
public:
	Bullet(glm::vec3 position, float rotation, glm::vec3 size);
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;

	void Shoot(glm::vec3 position);
	
	inline const glm::vec3& GetPosition() const { return position; }
	inline const glm::vec3& GetSize() const { return scale; }
	inline void const SetSpeed(float s) { speed = s; }
	inline void const SetPlayerOrEnemy(int i) { player_or_enemy = i; }
	inline bool const IsShooting() const { return isShoot; }
	inline void Destroy() override { isShoot = false; }
private:
	bool isShoot = false;
	float speed = 2000.f;
	float time_to_dispear = 1;
	float time_btw = time_to_dispear;
	int player_or_enemy;
};