#include "MeshGenerator.h"
#define PI 3.14159265359f

void MeshGenerator::GenerateModel(std::string system, int iterations, std::string modelName, glm::vec3 startingPoint, float radius, int pointsPerLevel)
{
	m_model = new Model(modelName);
	m_model->GetMesh()->m_compileSAT = false;
	system = m_system.ApplyAxioms(system, iterations);
	std::vector< std::pair<glm::vec3, float>> pointCollections;
	std::vector<std::pair<glm::vec3, float>> pointStack;
	float translationOffset = 1.0f;
	float scaleOffset = 1.5f;
	glm::vec3 translationVector = glm::vec3(0, 1, 0);
	glm::quat rotation = glm::quat(glm::vec3(0, PI / 6, 0));
	for (int i = 0; i < system.size(); i++)
	{
		switch (system[i])
		{
		case 't': //translate
		case 'T':
			startingPoint += translationVector;
			break;
		case 's': //scale smaller
			radius /= scaleOffset;
			break;
		case 'S': //scale larger
			radius *= scaleOffset;
			break;
		case 'r': //rotate counter clockwise
			translationVector = glm::rotate(-rotation, translationVector);
			break;
		case 'R': //rotate clockwise
			translationVector = glm::rotate(-rotation, translationVector);
			break;
		case 'c':
		case 'C':
			radius = .01f;
			break;
		case '[': //push point onto the stack
			pointStack.push_back(std::make_pair(startingPoint, radius));
			break;
		case ']': { //pop point from the stack
			std::pair<glm::vec3, float> popped = pointStack.back();
			pointStack.pop_back();
			startingPoint = popped.first;
			radius = popped.second;
		}
			break;
		case '+': //pushes the current point to be used on the geometry
			pointCollections.push_back(std::make_pair(startingPoint, radius));
			break;
		default:
			break;
		}
	}
	//Create the vertices for the mesh
	std::vector<std::vector<glm::vec3>> meshGeometry;
	for (int i = 0; i < pointCollections.size(); i++)
	{
		std::vector<glm::vec3> pointsForIteration;
		for (int n = 0; n < pointsPerLevel; n++)
		{
			glm::vec3 vertex;
			vertex = pointCollections[i].first;
			float r = pointCollections[i].second;
			vertex.x += r * cos(2 * PI / pointsPerLevel * n );
			vertex.z += r * sin(2 * PI / pointsPerLevel * n);
			pointsForIteration.push_back(vertex);
		}
		meshGeometry.push_back(pointsForIteration);
	}
	//Create the face geometry for the mesh
	for (int i = 0; i < meshGeometry.size(); i++)
	{
		int currentSize = meshGeometry[i].size();
		int nextRowSize = meshGeometry[(i + 1) % meshGeometry.size()].size();
		for (int k = 0; k < currentSize; k++)
		{
			//Draw to the next layer of points, unless this is the first or last layer.
			//In those situations the shape needs to close, so connect those to the center points.
			if (i == 0)
			{
				m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], pointCollections[i].first);
			}
			if (i == meshGeometry.size() - 1)
			{
				m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], pointCollections[i].first);
				continue; //There are no more points to draw up to
			}
			//Need to draw the face
			// __
			//|\ |
			//|_\|
			//Two triangles per face
			//Draw the first triangle of the face
			m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], meshGeometry[i + 1][k]);
			m_model->AddTri(meshGeometry[i + 1][k], meshGeometry[i + 1][(k + 1) % currentSize], meshGeometry[i][(k + 1) % currentSize]);
		}
	}
	//Call compile shape to do this when this function is called instead of when the object needs to be rendered
	m_model->compileShape();
}
