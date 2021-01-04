#pragma once

#include "glm/glm.hpp"
#include "SpriteRenderer.h"

class GameObject 
{
public:
	GameObject();
	virtual void OnInit(glm::vec3 position, float rotation, glm::vec3 size);
	virtual void OnUpdate(float ds) {}
	virtual void OnRender(SpriteRenderer* renderer) {}
	virtual void Destroy() {}

	inline const glm::vec3& GetPosition() const { return position; }
	inline const float GetRotation() const { return rotation; }
	inline const glm::vec3& GetSize() const { return scale; }
protected:
	glm::vec3 position;
	float rotation;
	glm::vec3 scale;
};