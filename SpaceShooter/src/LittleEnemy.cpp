#include "LittleEnemy.h"

LittleEnemy::LittleEnemy()
{
	this->position = glm::vec3(0);
	this->rotation = 0;
	this->scale = glm::vec3(1);
}

void LittleEnemy::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;

	bar = new HealthBar();
	bar->OnInit(glm::vec3(1000, 1000, 0 ), 0, glm::vec3(80, 10, 0));
	bar->SetColor(glm::vec4(1, 0, 0, 1));
	max_health = bar->GetScaleX();
	health = max_health;
}

void LittleEnemy::OnUpdate(float ds)
{
	if (isAlive)
	{
		bar->SetPositoin(glm::vec3(position.x-adjust_health_bar, position.y + 50, 0));
		position.y -= speed * ds;
	}

	if (isAlive && position.y <= -420)
		Destroy();

	// Check is dead or not
	if (health <= 0)
		Destroy();
}

void LittleEnemy::OnRender(SpriteRenderer* renderer)
{
	if (isAlive)
	{
		renderer->Draw(Texture::GetTexture("littleEnemy"), Shader::GetShader("sprite"), position, rotation, scale, glm::vec4(1), glm::mat4(1));
		bar->OnRender(renderer);
	}
}

void LittleEnemy::Spaw(glm::vec3 spawnPosition)
{
	health = max_health;

	position = spawnPosition;
	speed = 1 + rand() % 50 + 180;

	bar->SetAlive(true);
	isAlive = true;
}

void LittleEnemy::TakeDamage(int i)
{
	health -= i;
	bar->SetScaleX(health);
	adjust_health_bar = max_health / 2.f * (float(health) / float(max_health));
}

inline void LittleEnemy::Destroy()
{
	isAlive = false; bar->SetAlive(false); 
	bar->SetScaleX(max_health); 
	bar->SetPositoin(glm::vec3(1000, 1000, 0));
}

LittleEnemy::~LittleEnemy()
{
	delete bar;
}
