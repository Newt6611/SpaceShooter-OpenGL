#include "Heart.h"

void Heart::OnInit(glm::vec3 position, float rotation, glm::vec3 size)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = size;
}

void Heart::OnUpdate(float ds)
{
}

void Heart::OnRender(SpriteRenderer* renderer)
{
	
	for (int i = 0; i < count; i++)
	{
		renderer->Draw(Texture::GetTexture("heart"), Shader::GetShader("sprite"), 
			glm::vec3(position.x + i * 45, position.y, position.z), rotation, scale, m_Color, glm::mat4(1));
	}
}
