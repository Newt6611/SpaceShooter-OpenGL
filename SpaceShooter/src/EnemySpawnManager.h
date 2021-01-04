#pragma once
#include "GameObject.h"
#include "LittleEnemy.h"

#include <vector>

class EnemySpawnManager : public GameObject
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;
	void Destroy() override { isAlive = false; }

	void SpawLittleEnemy();

	std::vector<LittleEnemy*> GetEnemys() { return littleEnemys; }

private:
	std::vector<LittleEnemy*> littleEnemys;
	int little_enemy_index = 0;
	int max_littleEnemy = 20;
	float time_to_spawn = 3;
	float time_btw = time_to_spawn;
	bool isAlive;
};