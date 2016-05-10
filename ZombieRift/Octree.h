#pragma once
#include "Model.h"
#include "GameObject.h"

class Octree {
private:
	Model* m_cube;
	glm::vec3 m_position;
	glm::vec3 m_size;
	glm::vec3 m_max;
	glm::vec3 m_min;
	Octree* m_parent;

	void ReBound();
public:
	std::vector<Octree*> m_children;
	std::vector<GameObject*> m_gameObjects;

	void AddNode(GameObject* object);

	void SubDivide();

	void Render();
};