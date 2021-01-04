#pragma once
#include "GameObject.h"
#include "Heart.h"
#include "Bullet.h"
#include <vector>

enum class BossState {
	sleep = 0, fight, dead
};

class Boss : public GameObject
{
public:
	Boss();
	~Boss();
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;
	void Destroy() override { isAlive = false; }
	void TakeDamage();

	inline const std::vector<Bullet*> GetBullets() const { return bulletPool; }
	
	inline const void SetPlayerPosition(float x) { this->player_position.x = x; }
	inline const bool IsAlive() const { return isAlive; }
	inline const void SetAlive(bool a) { isAlive = a; state = BossState::fight; }
	inline const BossState GetState() const { return state; }
private:
	void InitBulletPool();
	void TracePlayer(float ds);
	void Shoot();

private:
	BossState state;
	Heart* heart;
	int health;
	bool isAlive;
	float speed = 95;

	std::vector<Bullet*> bulletPool;
	int bulletIndex = 0;
	int maxBullet = 30;

	glm::vec3 player_position = glm::vec3(0);

	bool startShoot;
	float time_to_shoot = 1.f;
	float time_btw = time_to_shoot;
};