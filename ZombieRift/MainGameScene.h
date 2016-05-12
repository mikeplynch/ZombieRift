#pragma once

#include "GameManager.h"
#include "SimpleObjects.h"
#include "Player.h"
#include "KinectUtilites.h"

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