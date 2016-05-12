#pragma once

#include "GameObject.h"

class BasicGun : public GameObject
{
private:
	GameObject* m_shooter;

	BasicGun();

public:
	~BasicGun();

	BasicGun(GameObject* shooter);

	virtual void Update(float dt) override;
};