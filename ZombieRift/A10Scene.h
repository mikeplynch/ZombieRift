#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"
#include "Player.h"
#include "Zombie.h"

class A10Scene : public Scene {
	BoxObject* box;
	PlayerBox* player;
	virtual void Init();
	virtual void Update(float dt);

	void HandleInput(Camera* camera);
};


class A11Scene : public A10Scene { };

class MainGameScene : public Scene
{
private:
	const int m_maxZombies = 10;
	const int m_zombieThreshold = 10; // For every X zombies you kill, spawn an extra zombie each time.

	BoxObject* box;
	Player* player;
	//std::vector<Zombie*> zombies;
	
	virtual void Init();

public:
	virtual void Update(float dt);

	void AddZombie(glm::vec3 target);
	void AddZombies(int playerScore, int pointsPerZombie);
};