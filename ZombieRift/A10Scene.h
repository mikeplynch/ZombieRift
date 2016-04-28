#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"

class A10Scene : public Scene {
	BoxObject* box;
	PlayerBox* player;
	virtual void Init();
	virtual void Update();

	void HandleInput(Camera* camera);
};