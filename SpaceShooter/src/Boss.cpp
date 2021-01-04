#include "Boss.h"
#include "Input.h"
Boss::Boss()
{
}

void Boss::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;

	isAlive = false;

	health = 10;
	heart = new Heart();
	heart->OnInit(glm::vec3(-240 + 35, 400 - 35, 0), 0, glm::vec3(40));
	heart->InitCount(health);
	heart->SetColor(glm::vec4(0.568, 0, 0.46, 1)); // purple

	InitBulletPool();
	state = BossState::sleep;
}

void Boss::OnUpdate(float ds)
{
	if (isAlive && position.y >= 200)
		position.y -= speed * ds;

	if (isAlive && position.y <= 200)
	{
		TracePlayer(ds);
		startShoot = true;
	}

	if (isAlive && startShoot)
	{
		for (int i = 0; i < maxBullet; i++)
			bulletPool[i]->OnUpdate(ds);
	
		if (time_btw <= 0) {
			Shoot();
		}
		else {
			time_btw -= ds;
		}
	}
}

void Boss::OnRender(SpriteRenderer* renderer)
{
	if (isAlive)
	{
		renderer->Draw(Texture::GetTexture("boss"), Shader::GetShader("sprite"), position, rotation, scale, glm::vec4(1), glm::mat4(1));
		heart->OnRender(renderer);
		
		for (int i = 0; i < maxBullet; i++)
			bulletPool[i]->OnRender(renderer);
	}
}

void Boss::TakeDamage()
{
	health -= 1; 
	heart->InitCount(health); 
	if (health <= 0) 
	{
		isAlive = false; 
		state = BossState::dead;
	}
}

void Boss::InitBulletPool()
{
	for (int i = 0; i < maxBullet; i++)
	{
		bulletPool.push_back(new Bullet(glm::vec3(position.x, position.y - 40, position.z), 0, glm::vec3(30)));
		bulletPool[i]->SetPlayerOrEnemy(-1);
	}
}

void Boss::Shoot()
{
	time_btw = time_to_shoot;
	bulletPool[bulletIndex]->Shoot(glm::vec3(position.x, position.y - 40, 0));
	bulletIndex++;
	if (bulletIndex >= maxBullet)
		bulletIndex = 0;
}

void Boss::TracePlayer(float ds)
{
	if (abs(position.x - this->player_position.x) >= 5)
	{
		// trace 
		if (player_position.x - position.x > 0)
			position.x += speed * ds;
		else if (player_position.x - position.x < 0)
			position.x -= speed * ds;
	}
}

Boss::~Boss()
{
	delete heart;
}