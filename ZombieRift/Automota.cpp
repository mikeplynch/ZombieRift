#include "Automota.h"

Colony::Colony(int length, int width, int height)
{
	this->length = length;
	this->width = width;
	this->height = height;
	//Setup cell sizes
	cells.resize(height);
	for (int h = 0; h < height; h++) 
	{
		cells[h].resize(width);
		for (int w = 0; w < width; w++)
		{
			cells[h][w].resize(length);
			for (int l = 0; l < length; l++)
			{
				cells[h][w][l] = new Automota(this, h, w, l);
			}
		}
	}

	//Do this after every location has been set to avoid null values
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			for (int l = 0; l < length; l++)
			{
				cells[h][w][l]->DetermineNeighbors();
			}
		}
	}
}

void Colony::AddToScene(Scene * target)
{
	for (int h = 0; h < this->height; h++)
	{
		for (int w = 0; w < this->width; w++)
		{
			for (int l = 0; l < this->length; l++)
			{
				target->AddObject(cells[h][w][l]);
			}
		}
	}
}


Automota::Automota(Colony * col, int h, int w, int l)
{
	m_colony = col;
	m_index = glm::vec3(h, w, l);
	m_neighbors = new std::vector<Automota*>();
	m_collisionData = new CollisionData(m_model, this);
	m_collisionData->m_collisionMask = 0;
	
}

void Automota::DetermineNeighbors()
{
	std::vector<std::vector<std::vector<Automota*>>> cells = m_colony->cells;
	int h = m_index.x;
	int w = m_index.y;
	int l = m_index.z;
	int height = m_colony->height;
	int length = m_colony->length;
	int width = m_colony->width;
	if(!(h + -1 >= height || h + -1 < 0 || w + 1  >= width || w + 1  < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + -1][w + 1 ][l + 1]);
	if(!(h + -1 >= height || h + -1 < 0 || w + 0  >= width || w + 0  < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + -1][w + 0 ][l + 1]);
	if(!(h + -1 >= height || h + -1 < 0 || w + -1 >= width || w + -1 < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + -1][w + -1][l + 1]);
	if(!(h + 0  >= height || h + 0  < 0 || w + 1  >= width || w + 1  < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + 0 ][w + 1 ][l + 1]);
	if(!(h + 0  >= height || h + 0  < 0 || w + 0  >= width || w + 0  < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + 0 ][w + 0 ][l + 1]);
	if(!(h + 0  >= height || h + 0  < 0 || w + -1 >= width || w + -1 < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + 0 ][w + -1][l + 1]);
	if(!(h + 1  >= height || h + 1  < 0 || w + 1  >= width || w + 1  < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + 1 ][w + 1 ][l + 1]);
	if(!(h + 1  >= height || h + 1  < 0 || w + 0  >= width || w + 0  < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + 1 ][w + 0 ][l + 1]);
	if(!(h + 1  >= height || h + 1  < 0 || w + -1 >= width || w + -1 < 0 || l + 1  >= length || l + 1  < 0 ))m_neighbors->push_back(cells[h + 1 ][w + -1][l + 1]);
			  	
	if(!(h + -1 >= height || h + -1 < 0 || w + 1  >= width || w + 1  < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + -1][w + 1 ][l + 0]);
	if(!(h + -1 >= height || h + -1 < 0 || w + 0  >= width || w + 0  < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + -1][w + 0 ][l + 0]);
	if(!(h + -1 >= height || h + -1 < 0 || w + -1 >= width || w + -1 < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + -1][w + -1][l + 0]);
	if(!(h + 0  >= height || h + 0  < 0 || w + 1  >= width || w + 1  < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + 0 ][w + 1 ][l + 0]);
	if(!(h + 0  >= height || h + 0  < 0 || w + -1 >= width || w + -1 < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + 0 ][w + -1][l + 0]);
	if(!(h + 1  >= height || h + 1  < 0 || w + 1  >= width || w + 1  < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + 1 ][w + 1 ][l + 0]);
	if(!(h + 1  >= height || h + 1  < 0 || w + 0  >= width || w + 0  < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + 1 ][w + 0 ][l + 0]);
	if(!(h + 1  >= height || h + 1  < 0 || w + -1 >= width || w + -1 < 0 || l + 0  >= length || l + 0  < 0 ))m_neighbors->push_back(cells[h + 1 ][w + -1][l + 0]);
				
	if(!(h + -1 >= height || h + -1 < 0 || w + 1  >= width || w + 1  < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + -1][w + 1 ][l + -1]);
	if(!(h + -1 >= height || h + -1 < 0 || w + 0  >= width || w + 0  < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + -1][w + 0 ][l + -1]);
	if(!(h + -1 >= height || h + -1 < 0 || w + -1 >= width || w + -1 < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + -1][w + -1][l + -1]);
	if(!(h + 0  >= height || h + 0  < 0 || w + 1  >= width || w + 1  < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + 0 ][w + 1 ][l + -1]);
	if(!(h + 0  >= height || h + 0  < 0 || w + 0  >= width || w + 0  < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + 0 ][w + 0 ][l + -1]);
	if(!(h + 0  >= height || h + 0  < 0 || w + -1 >= width || w + -1 < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + 0 ][w + -1][l + -1]);
	if(!(h + 1  >= height || h + 1  < 0 || w + 1  >= width || w + 1  < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + 1 ][w + 1 ][l + -1]);
	if(!(h + 1  >= height || h + 1  < 0 || w + 0  >= width || w + 0  < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + 1 ][w + 0 ][l + -1]);
	if(!(h + 1  >= height || h + 1  < 0 || w + -1 >= width || w + -1 < 0 || l + -1 >= length || l + -1 < 0 ))m_neighbors->push_back(cells[h + 1 ][w + -1][l + -1]);
}

void Automota::update()
{
	m_translations = m_colony->worldPosition + m_index * m_colony->spacing;
	if (m_state < 1) {
		m_visible = false;
	}
	else {
		m_visible = true;
	}
}
