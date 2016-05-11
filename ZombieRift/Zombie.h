#pragma once

#include "GameObject.h"
#include "SimpleObjects.h"

class Zombie : public GameObject
{
private:
	int m_points = 100;

	float m_moveSpeed = 2.0f;
	glm::vec3 m_target;

	virtual void onCollision(GameObject* other) override;

	Zombie();
protected:
	virtual void CleanUp() override;
public:

	~Zombie();

	Zombie(glm::vec3 position, glm::vec3 target);

	virtual void Update(float dt) override;

	const int GetPoints() { return m_points; }
};
