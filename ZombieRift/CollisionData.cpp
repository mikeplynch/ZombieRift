#include "CollisionData.h"

CollisionData::CollisionData(Shape* collisionBase)
{
	SetModel(collisionBase);
}

void CollisionData::GenerateBoundingBox()
{
	std::vector<glm::vec3> vertices = m_shape->GetVertices();
	if (vertices.size() > 0) {
		m_max = vertices[0];
		m_min = vertices[0];
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].x > m_max.x)
			m_max.x = vertices[i].x;
		else if (vertices[i].x < m_min.x)
			m_min.x = vertices[i].x;

		if (vertices[i].y > m_max.y)
			m_max.y = vertices[i].y;
		else if (vertices[i].y < m_min.y)
			m_min.y = vertices[i].y;

		if (vertices[i].x > m_max.z)
			m_max.z = vertices[i].z;
		else if (vertices[i].x < m_min.z)
			m_min.z = vertices[i].z;
	}

	m_size.x = glm::distance(glm::vec3(m_min.x, 0.0f, 0.0f), glm::vec3(m_max.x, 0.0f, 0.0f));
	m_size.y = glm::distance(glm::vec3(0.0f, m_min.y, 0.0f), glm::vec3(0.0f, m_max.y, 0.0f));
	m_size.z = glm::distance(glm::vec3(0.0f, 0.0f, m_min.z), glm::vec3(0.0f, 0.0f, m_max.z));
}

void CollisionData::SetModel(Shape* shape)
{
	if (m_shape != nullptr)
	{
		delete m_shape;
	}

	m_shape = shape;
	GenerateBoundingBox();
}