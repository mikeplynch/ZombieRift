#pragma once
#include "Model.h"
#include "CollisionData.h"
#include "Camera.h"

class Model;

///<summary>
///The base game object used by the engine.  This is the base object, and
///must always be inherited from.  For a test object use any of the objects
///in SimpleObjects.h
///</summary>
class GameObject {
	friend class CollisionData;
private:

protected:
	GameObject();
	~GameObject();
	Model* m_model;
	Camera* m_worldCamera;
public:
	//TODO: add variables for world position, rotation, and scale and implement
	//them automatically being utilized in draw.
	///<summary>
	///This is the primary transformation matrix for the game object.
	///Do all scaling, translations, rotations into this matrix.
	///</summary>
	glm::mat4 m_transformations = glm::mat4(0.0f);

	glm::vec3 m_translations = glm::vec3(0, 0, 0);
	glm::mat4 m_rotations = glm::mat4(1.0f);
	glm::vec3 m_scales = glm::vec3(1.0f, 1.0f, 1.0f);

	///<summary>
	///The primary purpose of this hash map is so that users of GameObjects can
	///add elements "on the fly" to a game object without having to create a new
	///variable every time.
	///</summary>
	std::map<std::string, int>* m_data;

	std::string m_name = "default";

	bool m_visible = true;

	CollisionData* m_collisionData;

	Model* GetModel();

	///<summary>
	///Update function must be implemented. Game object must be inherited form to use.
	///</summary>
	virtual void Update() = 0;

	///<Summary>
	///This function is called whenever a collision between two objects happens. Use this
	///To determine what to do as a response.
	///</summary>
	virtual void onCollision(GameObject* other) {};
	
	void SetModel(Model* model);
	void SetColor(glm::vec3 color);

	virtual void Draw();
	virtual void DrawDebug();

	void EnableCollision();
	
protected:
	void CreateModel(std::string name);
};