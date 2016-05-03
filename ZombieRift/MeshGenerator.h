#pragma once
#include "LSystem.h"
#include "Model.h"
#include "glm\gtc\constants.hpp"

class MeshGenerator {
public:
	LSytem m_system;
	Model* m_model;
	void GenerateModel(std::string system, int iterations, std::string modelName, glm::vec3 startingPoint, float radius, int pointsPerLevel);

private:

};