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

void Colony::Update()
{
	for (int h = 0; h < this->height; h++)
	{
		for (int w = 0; w < this->width; w++)
		{
			for (int l = 0; l < this->length; l++)
			{
				cells[h][w][l]->m_state = cells[h][w][l]->m_nextState;
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

void Colony::RandomizeState(int percentage)
{
	for (int h = 0; h < this->height; h++)
	{
		for (int w = 0; w < this->width; w++)
		{
			for (int l = 0; l < this->length; l++)
			{
				if (rand() % 100 >= percentage)
				{
					cells[h][w][l]->m_state = 1;
				}
			}
		}
	}
}


Automota::Automota(Colony * col, int h, int w, int l)
{
	m_colony = col;
	m_index = glm::vec3(h, w, l);
	m_neighbors = new std::vector<Automota*>();
	EnableCollision();
	m_collisionData->m_collisionMask = 0;
	m_model->GenCube(1.0f);
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

void Automota::Update()
{
	int living = countNeighbors();
	if (m_state > 0)
	{
		if (living < 2)
		{
			m_nextState = 0;
		}
		if (living == 2 || living == 3)
		{
			m_nextState = 1;
		}
		if (living > 3)
		{
			m_nextState = 0;
		}
	}
	else if (living == 3)
	{
		m_nextState = 1;
	}
	m_translations = m_colony->worldPosition + m_index * m_colony->spacing;
	if (m_state < 1) {
		m_visible = false;
	}
	else {
		m_visible = true;
	}
}

int Automota::countNeighbors()
{
	int n = 0;
	for (int i = 0; i < m_neighbors->size(); i++)
	{
		if (m_neighbors->at(i)->m_state > 0)
		{
			n++;
		}
	}
	return n;
}


