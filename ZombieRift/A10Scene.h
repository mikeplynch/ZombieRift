#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"
#include "Player.h"

class A10Scene : public Scene {
	BoxObject* box;
	PlayerBox* player;
	virtual void Init();
	virtual void Update();

	void HandleInput(Camera* camera);
};


class A11Scene : public A10Scene { };

class MainGameScene : public Scene
{
private:
	BoxObject* box;
	Player* player;
	
	virtual void Init();

public:
	virtual void Update();
};