#include "MainGameScene.h"
#include "Bullet.h"
#include "Zombie.h"
#include "BasicGun.h"

void MainGameScene::Init()
{
	//box = new BoxObject(1.0f, 10.0f, 2.0f);
	//box->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	//box->m_translations = glm::vec3(0.0f, 1.0f, -15.0f);
	//AddObject(box);

	player = new Player();

	for (unsigned int i = 0; i < m_maxZombies; i++)
	{
		AddZombie(player->m_translations);
	}


	AddObject(player);
	AddObject(player->GetReticle());
	AddObject(player->GetGun());
}

void MainGameScene::Update(float dt)
{

}

void MainGameScene::AddZombie(glm::vec3 target)
{
	int x = rand() % 20 - 10; // -10 to +10
	int y = 0;
	int z = rand() % 20 - 40; // -40 to -20

	Zombie* zombie = new Zombie(glm::vec3(x, y, z), target);
	AddObject(zombie);
}

void MainGameScene::AddZombies(int playerScore, int pointsPerZombie)
{
	unsigned int numZombiesKilled = (playerScore / pointsPerZombie);
	unsigned int numZombiesToAdd = (numZombiesKilled / m_zombieThreshold) + 1; // For every X zombies you kill, spawn an extra zombie each time.

	for (unsigned int i = 0; i < numZombiesToAdd; i++)
	{
		AddZombie(player->m_translations);
	}
}