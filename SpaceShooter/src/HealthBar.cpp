#include "HealthBar.h"

HealthBar::HealthBar()
{
}

void HealthBar::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
	isAlive = false;
}

void HealthBar::OnUpdate(float ds)
{
}

void HealthBar::OnRender(SpriteRenderer* renderer)
{
	if (isAlive)
	{
		//renderer->Draw(Shader::GetShader("health"), position, rotation, glm::vec3(80, 10 ,0), glm::vec4(1, 1, 1, 1), glm::mat4(1));
		renderer->Draw(Shader::GetShader("health"), position, rotation, scale, m_color, glm::mat4(1));
	}
}
