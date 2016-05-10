#pragma once
#include "Gravity.h"

class Bouncing : Scene {
	GravityObject* ball;
	glm::vec3 force;
	glm::vec3 grav;

	virtual void Init();

	virtual void Update(float dt);

};
