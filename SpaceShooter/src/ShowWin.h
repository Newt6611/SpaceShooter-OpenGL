#pragma once

#include "GameObject.h"

class ShowWin : public GameObject 
{
public:
	ShowWin() {}
	void OnInit(glm::vec3 position, float rotation, glm::vec3 size) override;
	void OnUpdate(float ds) override;
	void OnRender(SpriteRenderer* renderer) override;
	void ShowWinUI(GameObject* player, GameObject* boss, GameObject* enemySpawner);
private:
	bool isWin;
};