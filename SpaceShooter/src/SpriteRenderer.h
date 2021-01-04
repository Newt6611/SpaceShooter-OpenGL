#pragma once

#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"

class SpriteRenderer
{
public:
	SpriteRenderer();

	void Draw(Texture& texture, Shader& shader, glm::vec3 position, float rotation, glm::vec3 size, glm::vec4 color, glm::mat4 view);
	void Draw(Shader& shader, glm::vec3 position, float rotation, glm::vec3 size, glm::vec4 color, glm::mat4 view);

private:
	unsigned int vao, ibo;
};