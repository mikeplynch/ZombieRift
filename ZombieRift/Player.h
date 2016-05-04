#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Player : public GameObject
{
private:
	float m_moveSpeed = 0.01f;

	std::vector<Bullet*> m_bullets;

	virtual void onCollision(GameObject* other) override;
	void HandleInput(float dt);
	
	void MoveSideways(float dist);
	void MoveVertical(float dist);
	void MoveForward(float dist);

	void ChangeLookPitch(float degrees);
	void ChangeLookYaw(float degrees);
	void ChangeLookRoll(float degrees); // Probably never needed

	void Shoot();
	void CheckBullets();

	void ClearBullets();

public:
	Player();
	~Player();

	virtual void Update(float dt) override;

	std::vector<Bullet*> GetBullets() { return m_bullets; }
};
