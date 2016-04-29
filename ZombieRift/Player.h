#pragma once

#include "GameObject.h"

class Player : public GameObject
{
private:
	float m_moveSpeed = 0.01f;

	void HandleInput();
	
	void MoveSideways(float dist);
	void MoveVertical(float dist);
	void MoveForward(float dist);

	void ChangeLookPitch(float degrees);
	void ChangeLookYaw(float degrees);
	void ChangeLookRoll(float degrees); // Probably never needed

public:
	Player();
	~Player();

	virtual void Update() override;
};
