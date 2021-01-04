#include "Bullet.h"

Bullet::Bullet(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
}

void Bullet::OnUpdate(float ds)
{
	if (isShoot)
	{
		position.y += player_or_enemy * speed * ds;

		if (time_btw > 0) 
		{
			time_btw -= ds;
		}
		else 
		{
			time_btw = time_to_dispear;
			isShoot = false;
		}
	}
}

void Bullet::OnRender(SpriteRenderer* renderer)
{
	if (isShoot)
		renderer->Draw(Texture::GetTexture("bullet"), Shader::GetShader("sprite"), position, rotation, scale, glm::vec4(1), glm::mat4(1));
}

void Bullet::Shoot(glm::vec3 position)
{
	this->position = position;
	isShoot = true;
}
