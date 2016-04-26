#include "Automota.h"

colony::colony(int length, int width, int height)
{
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
				cells[h][w][l] = automota();
			}
		}
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			for (int l = 0; l < length; l++)
			{
				cells[h][w][l] = automota(cells, h, w, l);
			}
		}
	}
}

void automota::DetermineNeighbors(std::vector<std::vector<std::vector<automota>>>& cells, int h, int w, int l)
{
	m_neighbors.push_back(cells[h + -1][w + 1 ][l + 1]);
	m_neighbors.push_back(cells[h + -1][w + 0 ][l + 1]);
	m_neighbors.push_back(cells[h + -1][w + -1][l + 1]);
	m_neighbors.push_back(cells[h + 0 ][w + 1 ][l + 1]);
	m_neighbors.push_back(cells[h + 0 ][w + 0 ][l + 1]);
	m_neighbors.push_back(cells[h + 0 ][w + -1][l + 1]);
	m_neighbors.push_back(cells[h + 1 ][w + 1 ][l + 1]);
	m_neighbors.push_back(cells[h + 1 ][w + 0 ][l + 1]);
	m_neighbors.push_back(cells[h + 1 ][w + -1][l + 1]);

	m_neighbors.push_back(cells[h + -1][w + 1 ][l + 0]);
	m_neighbors.push_back(cells[h + -1][w + 0 ][l + 0]);
	m_neighbors.push_back(cells[h + -1][w + -1][l + 0]);
	m_neighbors.push_back(cells[h + 0 ][w + 1 ][l + 0]);
	m_neighbors.push_back(cells[h + 0 ][w + -1][l + 0]);
	m_neighbors.push_back(cells[h + 1 ][w + 1 ][l + 0]);
	m_neighbors.push_back(cells[h + 1 ][w + 0 ][l + 0]);
	m_neighbors.push_back(cells[h + 1 ][w + -1][l + 0]);

	m_neighbors.push_back(cells[h + -1][w + 1 ][l + -1]);
	m_neighbors.push_back(cells[h + -1][w + 0 ][l + -1]);
	m_neighbors.push_back(cells[h + -1][w + -1][l + -1]);
	m_neighbors.push_back(cells[h + 0 ][w + 1 ][l + -1]);
	m_neighbors.push_back(cells[h + 0 ][w + 0 ][l + -1]);
	m_neighbors.push_back(cells[h + 0 ][w + -1][l + -1]);
	m_neighbors.push_back(cells[h + 1 ][w + 1 ][l + -1]);
	m_neighbors.push_back(cells[h + 1 ][w + 0 ][l + -1]);
	m_neighbors.push_back(cells[h + 1 ][w + -1][l + -1]);
}

void automota::update()
{
}
