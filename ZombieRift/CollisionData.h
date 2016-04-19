#pragma once
#include "Shape.h"

///<summary>
///This is the core collision data for every object.
///Every object has Axis-aligned bounding boxes.
///</summary>
class CollisionData 
{
private:
	CollisionData() {};

	Shape* m_shape;
public:
	glm::vec3 m_max, m_min, m_size;

	CollisionData(Shape* collisionBase);

	///<summary>
	///Generates a bounding box from the currently model assigned to the collision
	///Data.
	///</summary>
	void GenerateBoundingBox();

	void SetModel(Shape* shape);
};
