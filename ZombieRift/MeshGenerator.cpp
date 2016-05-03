#include "MeshGenerator.h"
#define PI 3.14159265359f

void MeshGenerator::GenerateModel(std::string system, int iterations, std::string modelName, glm::vec3 startingPoint, float radius, int pointsPerLevel)
{
	m_model = new Model(modelName);
	m_model->GetMesh()->compileSAT = false;
	system = m_system.ApplyAxioms(system, iterations);
	std::vector< std::pair<glm::vec3, float>> pointCollections;
	pointCollections.push_back(std::make_pair(startingPoint, radius));
	std::vector<std::pair<glm::vec3, float>> pointStack;
	float translationOffset = 1.0f;
	float scaleOffset = 1.5f;
	glm::vec3 translationVector = glm::vec3(1, 1, 1);
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
	for (int i = 0; i < pointCollections.size(); i++)
	{ 
	}
}
