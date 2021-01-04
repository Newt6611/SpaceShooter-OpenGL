#include "BackGround.h"

BackGround::BackGround()
	: view(1), speed(200), second_position(0)
{
}

void BackGround::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	// window width = 480;
	// window height = 800;
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
	second_position = glm::vec3(position.x, position.y + 800.f, position.z);
}

void BackGround::OnUpdate(float ds)
{
	position.y -= speed * ds;
	second_position.y -= speed * ds;

	// reset bg position
	if (this->position.y + this->scale.y / 2.f <= -400.f)
	{
		position = glm::vec3(0);
		second_position = glm::vec3(position.x, position.y + 800.f, position.z);
	}
}

void BackGround::OnRender(SpriteRenderer* renderer)
{
	renderer->Draw(Texture::GetTexture("bg"), Shader::GetShader("sprite"), position, rotation, scale, glm::vec4(1), view);
	renderer->Draw(Texture::GetTexture("bg"), Shader::GetShader("sprite"), second_position, rotation, scale, glm::vec4(1), view);
}
