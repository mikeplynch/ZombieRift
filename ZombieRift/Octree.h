#pragma once
#include "Model.h"
#include "GameObject.h"

class Octree {
private:
	Octree();
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

	/// <summary>
	/// When you create an Octree, you need to pass it a list of game objects for it to contain.
	/// It will then attempt to place and subdivide accordingly.
	/// <summary>
	Octree(std::vector<GameObject> contained);

	void AddNode(GameObject* object);

	void SubDivide();

	void Render();
};