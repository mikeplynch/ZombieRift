#pragma once
#include "MyMesh.h"

struct Triangle {	
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 edge1;
	glm::vec3 edge2;
	glm::vec3 edge3;
	glm::vec3 surfaceNormal;

	Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

private:
	Triangle();
};

class Shape : MyMesh {
private:
	bool m_needsCompilation = true;
	void compileShape();

	std::string m_shapeType;
	std::vector<Triangle> m_faces;
public:
	Shape();

	const std::vector<glm::vec3>& GetVertices() { return m_lVertexPos; }
	std::vector<Triangle> GetFaces() { return m_faces; }

	// When color is unspecied, defaultColor is used.
	// default is set to red when unset.
	glm::vec3 defaultColor; 

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

	//Creates a box with the designated colors for the faces
	void GenBox(std::vector<glm::vec3> points, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back);
	void GenBox(std::vector<glm::vec3> points, glm::vec3 color);
	void GenBox(std::vector<glm::vec3> points);
	void GenBox(float width, float length, float height, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back);
	void GenBox(float width, float length, float height, glm::vec3 color);
	void GenBox(float width, float length, float height);

	void clearVertices();

	void ReColor(glm::vec3 color);
};