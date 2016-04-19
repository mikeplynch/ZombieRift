#pragma once
#include "Shape.h"
#include "Camera.h"
#include "CollisionData.h"

///<summary>
///The base game object used by the engine.  This is the base object, and
///must always be inherited from.  For a test object use any of the objects
///in SimpleObjects.h
///</summary>
class GameObject {
private:

protected:
	GameObject();
	~GameObject();
	Shape* m_model;
	Camera* m_worldCamera;
public:
	//TODO: add variables for world position, rotation, and scale and implement
	//them automatically being utilized in draw.
	///<summary>
	///This is the primary transformation matrix for the game object.
	///Do all scaling, translations, rotations into this matrix.
	///</summary>
	glm::mat4 m_transformations;

	///<summary>
	///The primary purpose of this hash map is so that users of GameObjects can
	///add elements "on the fly" to a game object without having to create a new
	///variable every time.
	///</summary>
	std::map<std::string, int>* m_data;

	std::string m_name = "default";

	CollisionData* m_collisionData;

	///<summary>
	///Update function must be implemented. Game object must be inherited form to use.
	///</summary>
	virtual void update() = 0;

	///<Summary>
	///This function is called whenever a collision between two objects happens. Use this
	///To determine what to do as a response.
	///</summary>
	virtual void onCollision(GameObject* other) {};
	
	void SetModel(Shape* shape);
	void SetColor(glm::vec3 color) { m_model->ReColor(color); }

	virtual void draw();
};