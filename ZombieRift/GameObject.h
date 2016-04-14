#pragma once
#include "Shape.h"
#include "Camera.h"

class GameObject {
private:

protected:
	GameObject();
	Shape* m_model;
	Camera* m_worldCamera;
public:
	glm::mat4 m_transformations;

	virtual void update() = 0;

	void SetModel(Shape* shape) { m_model = shape; };
	void SetColor(glm::vec3 color) { m_model->defaultColor = color; }

	virtual void draw();
};

class CubeObject : public GameObject {
public:
	CubeObject();

	void update() { };
};