#pragma once
#include "MyMesh.h"


class Shape : MyMesh {
private:
	bool m_needsCompilation = true;
	void compileShape();

	std::string m_shapeType;
public:
	Shape();

	// When color is unspecied, defaultColor is used.
	// default is set to red when unset.
	glm::vec3 defaultColor = glm::vec3(1.0f, 0.0f, 0.0f); 

	void RenderShape(glm::mat4 toWorld, glm::mat4 view, glm::mat4 persp);

	void AddVertex(glm::vec3 position);
	void AddVertex(glm::vec3 position, glm::vec3 color);

	void AddColor(glm::vec3 color);

	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3);
	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color);
	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

	//Creates a cube with the designated colors for the faces
	void GenCube(float size, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back);
	void GenCube(float size, glm::vec3 color);
	void GenCube(float size);

	void clearVertices();

	void ReColor(glm::vec3 color);
};