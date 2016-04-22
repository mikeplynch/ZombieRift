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

void Shape::GenBox(std::vector<glm::vec3> points, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	if (points.size() < 8)
	{
		return;
	}
	
	//Front
	AddTri(points[1], points[3], points[0], front);
	AddTri(points[2], points[3], points[1], front);

	//Left
	AddTri(points[0], points[3], points[7], left);
	AddTri(points[4], points[0], points[7], left);

	//Right
	AddTri(points[1], points[5], points[6], right);
	AddTri(points[6], points[2], points[1], right);

	//Bottom
	AddTri(points[0], points[4], points[5], bottom);
	AddTri(points[5], points[1], points[0], bottom);

	//Top
	AddTri(points[2], points[6], points[7], top);
	AddTri(points[3], points[2], points[7], top);

	//Back
	AddTri(points[6], points[7], points[4], back);
	AddTri(points[5], points[6], points[4], back);

	//Set the shape to cube
	m_shapeType = "Box";
}

void Shape::GenBox(std::vector<glm::vec3> points, glm::vec3 color)
{
	GenBox(points, color, glm::vec3(0.0f,1.0f,0.0f), color, color ,color, color);
}

void Shape::GenBox(std::vector<glm::vec3> points)
{
	GenBox(points, defaultColor);
}

void Shape::GenBox(float width, float height, float length, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	//Create the eight points that will map out to the cube
	//remember counterclockwise to the tri is where the face will be visible

	width *= .5f;
	height *= .5f;
	length *= .5f;

	std::vector<glm::vec3> points(8, glm::vec3(0.0f));

	//Top points
	points[0] = glm::vec3(-width, -height, length);
	points[1] = glm::vec3(width, -height, length);
	points[2] = glm::vec3(width, height, length);
	points[3] = glm::vec3(-width, height, length);

	//Bottom points
	points[4] = glm::vec3(-width, -height, -length);
	points[5] = glm::vec3(width, -height, -length);
	points[6] = glm::vec3(width, height, -length);
	points[7] = glm::vec3(-width, height, -length);

	GenBox(points, front, left, right, bottom, top, back);
}

void Shape::GenBox(float width, float height, float length, glm::vec3 color)
{
	GenBox(width, height, length, color, color, color, color, color, color);
}

void Shape::GenBox(float width, float height, float length)
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
	this->color = color;
}

