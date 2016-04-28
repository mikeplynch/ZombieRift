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
	Shape* m_boundingBox;
	GameObject* m_object;

	static bool Overlaps(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2);

	void GenerateBoundingBox(std::vector<glm::vec3> vertices, glm::vec3& min, glm::vec3& max, glm::vec3& size);

public:
	glm::vec3 m_max, m_min, m_size, m_center;
	glm::vec3 m_reMax, m_reMin, m_reSize;
	std::vector<glm::vec3> m_boundingPoints;
	std::vector<glm::vec3> m_reBoundingPoints;

	enum CollisionDetectionType
	{
		BoundingBox = 0,
		AxisRealignedBoundingBox = 1,
	};

	CollisionData(Shape* collisionBase, GameObject* object);
	~CollisionData();

	///<summary>
	///The collision mask for an object.  Initial set to 1 so that every base collision object 
	///will collide with each other. The bitmask will bit-wise & two masks together and if the 
	///result is greater than 0 then collision will be checked. If a mask is set to 0 it will 
	///not check for any collisions.
	///</summary>
	int m_collisionMask = 0x1;

	///<summary>
	///Generate bounding boxes from the currently model assigned to the collision
	///Data.
	///</summary>
	void UpdateBoundingBoxes();

	static std::vector<glm::vec3> GenerateBoundingPoints(glm::vec3 min, glm::vec3 max);

	void SetModel(Shape* shape);

	void DrawBoundingBox();

	static bool AreColliding(CollisionDetectionType type, GameObject* first, GameObject* second);

	static std::vector<glm::vec3> GetEdgeAxes(GameObject * first, GameObject * second);

	static bool SeperatingAxisTest(GameObject* first, GameObject* second);
};