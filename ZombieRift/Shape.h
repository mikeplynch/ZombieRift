#pragma once
#include "MyMesh.h"

struct Face {	
	glm::vec3 edge1;
	glm::vec3 edge2;
	glm::vec3 edge3;
	glm::vec3 surfaceNormal;

	Face(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

private:
	Face();
};

class Shape : MyMesh {
private:
	bool m_needsCompilation = true;
	void compileShape();

	std::string m_shapeType;
	std::vector<Face> m_faces;
public:
	Shape();

	const std::vector<glm::vec3>& GetVertices() { return m_lVertexPos; }
	std::vector<Face> GetFaces() { return m_faces; }

	//<summary>
	//When color is unspecied, defaultColor is used. default is set to red when unset.
	//</summary>
	glm::vec3 m_defaultColor; 

	//<summary>
	//This is the speciailized list of edges that need to be cheked for SAT.
	//It is optimized to remove extra edges that will have already been accounted for by 
	//Other edges in the geometry.
	//</sumarry>
	std::vector<glm::vec3> m_SATEdges;
	//<summary>
	//Similar to the m_SATEEdges this is an optimized collection of face normals to use
	//with SAT.
	//</summary>
	std::vector<glm::vec3> m_SATNormals;
	//<summary>
	//This is the scaling vector used specifically by the shape class to optimize shape drawing
	//by only creating one of a primitive type of object.  A single object is used to draw every
	//shape of the same type, but scaled to fit the desired size.
	//</summary
	glm::vec3 m_oneTypeObjectScalar = glm::vec3(1, 1, 1);

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