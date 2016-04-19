#include "Shape.h"

void Shape::compileShape()
{
	m_bBinded = false;
	if (m_ColorBuffer > 0)
		glDeleteBuffers(1, &m_ColorBuffer);
	if (m_VertexBuffer > 0)
		glDeleteBuffers(1, &m_VertexBuffer);
	if (m_vao > 0)
		glDeleteVertexArrays(1, &m_vao);
	CompileOpenGL3X();
	m_needsCompilation = false;
}

Shape::Shape()
{
	m_shapeType = "none";
	defaultColor = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Shape::RenderShape(glm::mat4 toWorld, glm::mat4 view, glm::mat4 persp)
{
	if (m_needsCompilation) {
		compileShape();
	}
	Render(toWorld, view, persp);
}

void Shape::AddVertex(glm::vec3 position)
{
	AddVertexPosition(position);
	m_needsCompilation = true;

	switch (m_nVertexCount)
	{
	case 1:
		m_shapeType = "point";
		break;
	case 2:
		m_shapeType = "line";
		break;
	case 3:
		m_shapeType = "triangle";
		break;
	default:
		m_shapeType = "other";
	}
}

void Shape::AddVertex(glm::vec3 position, glm::vec3 color)
{
	AddVertex(position);
	AddVertexColor(color);
}

void Shape::AddColor(glm::vec3 color)
{
	AddVertexColor(color);
	m_needsCompilation = true;
}

void Shape::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3)
{
	AddVertex(point1);
	AddVertex(point2);
	AddVertex(point3);

	AddVertexColor(color1);
	AddVertexColor(color2);
	AddVertexColor(color3);
}

void Shape::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color)
{
	AddTri(point1, point2, point3, color, color, color);
}

void Shape::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	AddTri(point1, point2, point3, defaultColor, defaultColor, defaultColor);
}

void Shape::GenCube(float size, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	GenBox(size, size, size, front, left, right, bottom, top, back);
	m_shapeType = "Cube";
}

void Shape::GenCube(float size, glm::vec3 color)
{
	GenCube(size, color, color, color, color, color, color);
}

void Shape::GenCube(float size)
{
	GenCube(size, defaultColor);
}

void Shape::GenBox(float width, float length, float height, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	//Create the eight points that will map out to the cube
	//remember counterclockwise to the tri is where the face will be visible

	width *= .5f;
	length *= .5f;
	height *= .5f;

	//Top points
	glm::vec3 point0 = glm::vec3(-width, -height, length);
	glm::vec3 point1 = glm::vec3(width, -height, length);
	glm::vec3 point2 = glm::vec3(width, height, length);
	glm::vec3 point3 = glm::vec3(-width, height, length);

	//Bottom points
	glm::vec3 point4 = glm::vec3(-width, -height, -length);
	glm::vec3 point5 = glm::vec3(width, -height, -length);
	glm::vec3 point6 = glm::vec3(width, height, -length);
	glm::vec3 point7 = glm::vec3(-width, height, -length);

	//Front
	AddTri(point1, point3, point0, front);
	AddTri(point2, point3, point1, front);

	//Left
	AddTri(point0, point3, point7, left);
	AddTri(point4, point0, point7, left);

	//Right
	AddTri(point1, point5, point6, right);
	AddTri(point6, point2, point1, right);

	//Bottom
	AddTri(point0, point4, point5, bottom);
	AddTri(point5, point1, point0, bottom);

	//Top
	AddTri(point2, point6, point7, top);
	AddTri(point3, point2, point7, top);

	//Back
	AddTri(point6, point7, point4, back);
	AddTri(point5, point6, point4, back);

	//Set the shape to cube
	m_shapeType = "Box";

}

void Shape::GenBox(float width, float length, float height, glm::vec3 color)
{
	GenBox(width, length, height, color, color, color, color, color, color);
}

void Shape::GenBox(float width, float length, float height)
{
	GenBox(width, height, length, defaultColor);
}

void Shape::clearVertices()
{
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}

void Shape::ReColor(glm::vec3 color)
{
	defaultColor = color;
	m_lVertexCol.clear();
	for (int i = 0; i < m_lVertexPos.size(); i++)
	{
		AddColor(color);
	}
}

