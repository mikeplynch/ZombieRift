#include "A10Scene.h"

void A10Scene::Init()
{
	box = new BoxObject(1.0f, 10.0f, 2.0f);
	box->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	box->m_translations = glm::vec3(2.0f, 1.0f, 0.0f);
	box->m_name = "box";

	player = new PlayerBox();
	player->m_name = "player";
	player->m_translations = glm::vec3(-1.0f, 2.0f, -0.5f);

	MeshGenerator generator;
	//generator.GenerateModel("[c+]t+ttSS+t+ss+t+ss+", 1, "Dreidal", glm::vec3(0, 0, 0), .5f, 6);
	generator.m_system.AddAxiom('+', "+RTRT+");
	//generator.m_system.AddAxiom('a', "SSat+RRt[b]tsa");
	//generator.m_system.AddAxiom('b', "[c+][ttttSSS+]");
	generator.GenerateModel("+", 4, "Test1", glm::vec3(0, 0, 0), .5f, 20);

	player->SetModel(generator.m_model);

	AddObject(box);
	AddObject(player);
}

void A10Scene::Update()
{
	HandleInput(Camera::GetInstance());
}

void A10Scene::HandleInput(Camera* camera) {
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		camera->ChangeYaw(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		camera->ChangeYaw(-0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		camera->ChangePitch(-0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		camera->ChangePitch(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera->MoveSideways(-0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera->MoveSideways(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera->MoveForward(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera->MoveForward(-0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_Q))
	{
		camera->MoveVertical(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_E))
	{
		camera->MoveVertical(-0.1f);
	}
}

void MainGameScene::Init()
{
	box = new BoxObject(1.0f, 10.0f, 2.0f);
	box->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	box->m_translations = glm::vec3(0.0f, 1.0f, -15.0f);

	player = new Player();
	//player->m_translations = glm::vec3(0.0f, 2.0f, 0.0f);

	AddObject(box);
	AddObject(player);
}

void MainGameScene::Update()
{
	/* This is probably very bad and not correct. */
	for (unsigned int i = 0; i < player->GetBullets().size(); i++)
	{
		AddObject(player->GetBullets().at(i));
	}
}