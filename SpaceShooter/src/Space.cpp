#include "Space.h"

#include "Shader.h"
#include "Texture.h"
#include "Input.h"

// shoot position y + 35
Space::Space()
	: m_Color(1)
{}

void Space::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
	this->speed = 300.f;

	health = 10;
	heart = new Heart();
	heart->OnInit(glm::vec3(-240 + 35, -400 + 35, 0), 0, glm::vec3(40));
	heart->InitCount(health);
	heart->SetColor(glm::vec4(0.8, 0.8, 0.8, 1));

	isAlive = true;
}

void Space::OnUpdate(float ds)
{
	if (isAlive)
	{
		if (Input::GetKeyDown(GLFW_KEY_RIGHT))
			position.x += speed * ds;

		if (Input::GetKeyDown(GLFW_KEY_LEFT))
			position.x -= speed * ds;

		if (Input::GetKeyDown(GLFW_KEY_UP))
			position.y += speed * ds;

		if (Input::GetKeyDown(GLFW_KEY_DOWN))
			position.y -= speed * ds;

		EadgeDetection();
	}
}

void Space::OnRender(SpriteRenderer* renderer)
{
	if (isAlive)
	{
		renderer->Draw(Texture::GetTexture("space"), Shader::GetShader("sprite"), position, rotation, scale, m_Color, glm::mat4(1));
		heart->OnRender(renderer);
	}
}

void Space::EadgeDetection()
{
	if (position.x + scale.x / 2.f <= -240)
		position.x = 240;
	else if (position.x - scale.x / 2.f >= 240)
		position.x = -240;
}

Space::~Space()
{
	delete heart;
}
