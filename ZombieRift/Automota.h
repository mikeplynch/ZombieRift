#pragma once
#include "GameObject.h"
#include "GameManager.h"
class Colony;

class Automota : public GameObject {
private:
	std::vector<Automota*>* m_neighbors;
	Colony* m_colony;
	glm::vec3 m_index;
public:
	int m_state = 0;
	int m_nextState = 0;
	Automota() { };
	Automota(Colony* col, int h, int w, int l);
	virtual void DetermineNeighbors();
	void update();
	int countNeighbors();
};


class Colony {
private:
public:
	glm::vec3 worldPosition;
	float spacing = 1.0f;
	float cellSize = 1.0f;
	int length, width, height;
	std::vector<std::vector<std::vector<Automota*>>> cells;

	Colony(int length, int width, int height);
	void Update();

	void AddToScene(Scene* target);

	void RandomizeState(int percentage);
};