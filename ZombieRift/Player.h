#pragma once

#include "GameObject.h"
#include "Bullet.h"
#include "SimpleObjects.h"
#include "BasicGun.h"

class Player : public GameObject
{
private:
	int m_score = 0;
	float m_moveSpeed = 1.0f;
	float m_reticleSpeed = 0.01f;

	SphereObject* m_reticle;
	BasicGun* m_gun;
	std::vector<Bullet*> m_bullets;

	virtual void onCollision(GameObject* other) override;
	void HandleInput(float dt);

	void ChangeAimHorizontal(float dist);
	void ChangeAimVertical(float dist);
	
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
	
	void AddPoints(int points);

	SphereObject* GetReticle() { return m_reticle; }
	BasicGun* GetGun() { return m_gun; }
	std::vector<Bullet*> GetBullets() { return m_bullets; }
	const int GetScore() { return m_score; }
};
