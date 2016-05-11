#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private:
	GameObject* m_shooter;
	float m_speed = 0.1f;
	bool m_isAlive = true;

	glm::vec3 m_dir;

	float m_totalDistance;
	float m_maxDistance;

	virtual void onCollision(GameObject* other) override;

	Bullet();

protected:
	virtual void CleanUp() override;
public:
	~Bullet();

	Bullet(GameObject* shooter, glm::vec3 dir, float maxDistance);

	virtual void Update(float dt) override;

	bool IsAlive() { return m_isAlive; }
};