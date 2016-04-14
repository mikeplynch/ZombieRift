#pragma once
#include "Shape.h"
#include "Camera.h"
#include "CollisionData.h"

class GameObject {
private:

protected:
	GameObject();
	~GameObject();
	Shape* m_model;
	Camera* m_worldCamera;
	CollisionData* m_collisionData = nullptr;
public:
	//TODO: add variables for world position, rotation, and scale and implement
	//them automatically being utilized in draw.
	///<summary>
	///This is the primary transformation matrix for the game object.
	///Do all scaling, translations, rotations into this matrix.
	///<summary>
	glm::mat4 m_transformations;

	///<summary>
	///The primary purpose of this hash map is so that users of GameObjects can
	///add elements "on the fly" to a game object without having to create a new
	///variable every time.
	///</summary>
	std::map<std::string, int>* m_data;

	///<summary>
	///Update function must be implemented. Game object must be inherited form to use.
	///</summary>
	virtual void update() = 0;

	void SetModel(Shape* shape) { m_model = shape; };
	void SetColor(glm::vec3 color) { m_model->ReColor(color); }

	virtual void draw();
};