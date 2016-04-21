#include "CollisionData.h"
#define DEBUG false

CollisionData::CollisionData(Shape* collisionBase, GameObject* object)
{
	m_object = object;
	m_boundingPoints = std::vector<glm::vec3>(8, glm::vec3(0.0f));
	m_reBoundingPoints = std::vector<glm::vec3>(8, glm::vec3(0.0f));
	SetModel(collisionBase);
	m_boundingBox = new Shape();
	m_boundingBox->GenCube(1.0f);
}

CollisionData::~CollisionData()
{
	delete m_boundingBox;
}

void CollisionData::GenerateBoundingBox(std::vector<glm::vec3> vertices, glm::vec3& min, glm::vec3& max, glm::vec3& size)
{
	if (vertices.size() > 0) {
		max = vertices[0];
		min = vertices[0];
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].x > max.x)
			max.x = vertices[i].x;
		else if (vertices[i].x < min.x)
			min.x = vertices[i].x;

		if (vertices[i].y > max.y)
			max.y = vertices[i].y;
		else if (vertices[i].y < min.y)
			min.y = vertices[i].y;

		if (vertices[i].z > max.z)
			max.z = vertices[i].z;
		else if (vertices[i].z < min.z)
			min.z = vertices[i].z;
	}

	size.x = glm::distance(glm::vec3(min.x, 0.0f, 0.0f), glm::vec3(max.x, 0.0f, 0.0f));
	size.y = glm::distance(glm::vec3(0.0f, min.y, 0.0f), glm::vec3(0.0f, max.y, 0.0f));
	size.z = glm::distance(glm::vec3(0.0f, 0.0f, min.z), glm::vec3(0.0f, 0.0f, max.z));
}

void CollisionData::UpdateBoundingBoxes()
{

	/* The axis realigned bounding box */
	for (unsigned int i = 0; i < m_reBoundingPoints.size(); i++)
	{
		m_reBoundingPoints[i] = glm::vec3(m_object->m_transformations * glm::vec4(m_boundingPoints[i], 1.0f));
	}

	GenerateBoundingBox(m_reBoundingPoints, m_reMin, m_reMax, m_reSize);
	m_reBoundingPoints = GenerateBoundingPoints(m_reMin, m_reMax);

	m_center = (m_max + m_min) / 2.0f; // TC: Not sure if needed yet.
}

std::vector<glm::vec3> CollisionData::GenerateBoundingPoints(glm::vec3 min, glm::vec3 max)
{
	std::vector<glm::vec3> points(8, glm::vec3(0.0f));

	// Top Points
	points[0] = glm::vec3(min.x, min.y, max.z);
	points[1] = glm::vec3(max.x, min.y, max.z);
	points[2] = glm::vec3(max.x, max.y, max.z);
	points[3] = glm::vec3(min.x, max.y, max.z);

	// Bottom Points
	points[4] = glm::vec3(min.x, min.y, min.z);
	points[5] = glm::vec3(max.x, min.y, min.z);
	points[6] = glm::vec3(max.x, max.y, min.z);
	points[7] = glm::vec3(min.x, max.y, min.z);

	return points;
}

void CollisionData::SetModel(Shape* shape)
{
	if (m_shape != nullptr)
	{
		delete m_shape;
	}
	m_shape = shape;

	GenerateBoundingBox(m_shape->GetVertices(), m_min, m_max, m_size);
	m_boundingPoints = GenerateBoundingPoints(m_min, m_max);
	UpdateBoundingBoxes();
}

void CollisionData::DrawBoundingBox()
{
	//TODO: This currently only draws the REBB. Possibly add code to make it draw different ones
	//Depending on collision mode, or depending on debug mode.
	glm::mat4 world = glm::mat4(1.0f);
	world *= glm::translate(m_object->m_translations);
	world *= glm::scale(m_reSize);
	m_boundingBox->RenderShape(world, m_object->m_worldCamera->GetView(), m_object->m_worldCamera->GetProjection(false));
}

bool CollisionData::AreColliding(CollisionDetectionType type, GameObject* first, GameObject* second)
{
	bool areColliding = false;

	glm::vec3 min1(0.0f);
	glm::vec3 max1(0.0f);
	glm::vec3 min2(0.0f);
	glm::vec3 max2(0.0f);

	switch (type)
	{
	case BoundingBox:
		min1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_min, 1.0f));
		max1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_max, 1.0f));
		min2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_min, 1.0f));
		max2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_max, 1.0f));
		break;
	case AxisRealignedBoundingBox:
		min1 = first->m_collisionData->m_reMin;
		max1 = first->m_collisionData->m_reMax;
		min2 = second->m_collisionData->m_reMin;
		max2 = second->m_collisionData->m_reMax;
		break;
	default:
		assert("Unknown collision detection type.", false);
		break;
	}

	areColliding = AreCollidingBoundingBox(min1, max1, min2, max2);

	// TC: This shouldn't be here. We'll need to move it soon.
	if (DEBUG && areColliding)
	{
		first->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	return areColliding;
}

bool CollisionData::AreCollidingBoundingBox(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2)
{
	bool areColliding = true;
	
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

	return areColliding;
}