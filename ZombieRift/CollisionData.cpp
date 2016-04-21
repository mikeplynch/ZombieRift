#include "CollisionData.h"
#define DEBUG false

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

	m_center = (m_max + m_min) / 2.0f;
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

bool CollisionData::AreColliding(GameObject * first, GameObject * second)
{
	bool areColliding = true;
	glm::vec3 min1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_min, 1.0f));
	glm::vec3 max1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_max, 1.0f));
	glm::vec3 min2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_min, 1.0f));
	glm::vec3 max2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_max, 1.0f));

	if (std::max(max1.x, min1.x) < std::min(min2.x, max2.x))
		areColliding = false;
	if (std::min(min1.x, max1.x) > std::max(max2.x, min2.x))
		areColliding = false;

	if (std::max(max1.y, min1.y) < std::min(min2.y, max2.y))
		areColliding = false;
	if (std::min(min1.y, max1.y) > std::max(max2.y, min2.y))
		areColliding = false;

	if (std::max(max1.z, min1.z) < std::min(min2.z, max2.z))
		areColliding = false;
	if (std::min(min1.z, max1.z) > std::max(max2.z, min2.z))
		areColliding = false;

	if (DEBUG && areColliding)
	{
		first->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	return areColliding;
}
