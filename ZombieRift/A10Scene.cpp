#include "A10Scene.h"

void A10Scene::Init()
{
	box = new BoxObject(1.0f, 10.0f, 2.0f);
	box->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	box->m_translations = glm::vec3(2.0f, 1.0f, 0.0f);
	box->m_name = "box";

	BoxObject* box2 = new BoxObject(1.0f, 1.0f, 2.0f);
	box2->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	box2->m_translations = glm::vec3(-1.0f, 1.0f, -1.0f);
	box2->m_name = "box";

	player = new PlayerBox();
	player->m_name = "player";
	player->m_translations = glm::vec3(0.0f, 0.0f, 0.0f);

	AddObject(box);
	AddObject(player);
	AddObject(box2);
}

void A10Scene::Update(float dt)
{
	HandleInput(Camera::GetInstance());
}

void A10Scene::HandleInput(Camera* camera) {
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		camera->ChangeYaw(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		camera->ChangeYaw(-0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		camera->ChangePitch(-0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		camera->ChangePitch(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera->MoveSideways(-0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera->MoveSideways(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera->MoveForward(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera->MoveForward(-0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_Q))
	{
		camera->MoveVertical(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_E))
	{
		camera->MoveVertical(-0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_EQUAL))
	{
		if (toggle == false)
		{
			GameManager::GetInstance()->m_subdivisions++;
		}
		toggle = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_MINUS))
	{
		if (toggle == false)
		{
			GameManager::GetInstance()->m_subdivisions--;
			if (GameManager::GetInstance()->m_subdivisions < 0)
			{
				GameManager::GetInstance()->m_subdivisions = 0;
			}
		}
		toggle = true;
	}
	else 
	{
		toggle = false;
	}
}

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