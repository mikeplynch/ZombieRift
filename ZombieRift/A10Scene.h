#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"
#include "Player.h"
#include "Zombie.h"

class A10Scene : public Scene {
	BoxObject* box;
	PlayerBox* player;
	bool toggle = false;
	virtual void Init();
	virtual void Update(float dt);

	void HandleInput(Camera* camera);
};


class A11Scene : public A10Scene { };