#include "ShowWin.h"

void ShowWin::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
	isWin = false;
}

void ShowWin::OnUpdate(float ds)
{
	if (isWin && position.y >= 0)
		position.y -= 400 * ds;
}

void ShowWin::OnRender(SpriteRenderer* renderer)
{
	if (isWin)
	{
		renderer->Draw(Texture::GetTexture("win"), Shader::GetShader("sprite"), position, rotation, scale, glm::vec4(1), glm::mat4(1));
	}
}

void ShowWin::ShowWinUI(GameObject* player, GameObject* boss, GameObject* enemySpawner)
{
	isWin = true;
	player->Destroy();
	boss->Destroy();
	enemySpawner->Destroy();
}
