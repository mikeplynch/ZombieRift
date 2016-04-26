#pragma once
#include "GameObject.h"

class automota : GameObject {
private:
	std::vector<automota> m_neighbors;
public:
	automota() {};
	virtual void DetermineNeighbors(std::vector<std::vector<std::vector<automota>>>& cells, int h, int w, int l);
	void update();
};


class colony {
private:

public:
	int length, width, height;
	std::vector<std::vector<std::vector<automota>>> cells;

	colony(int length, int width, int height);
};