#pragma once
#include "GameObject.h"
extern class GameObject;

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
	glm::vec3 m_max, m_min, m_size, m_center;;

	CollisionData(Shape* collisionBase);

	///<summary>
	///The collision mask for an object.  Initial set to 1 so that every base collision object 
	///will collide with each other. The bitmask will bit-wise & two masks together and if the 
	///result is greater than 0 then collision will be checked. If a mask is set to 0 it will 
	///not check for any collisions.
	///</summary>
	int m_collisionMask = 0x1;

	///<summary>
	///Generates a bounding box from the currently model assigned to the collision
	///Data.
	///</summary>
	void GenerateBoundingBox();

	void SetModel(Shape* shape);

	static bool AreColliding(GameObject* first, GameObject* second);
};