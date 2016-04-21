#include "GameManager.h"

GameManager* GameManager::instance = nullptr;
GLFWwindow* GameManager::window = nullptr;

GameManager::GameManager()
{
}

GameManager * GameManager::GetInstance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		return instance = new GameManager();
	}
}

void GameManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void GameManager::SetCurrentScene(Scene* scene)
{
	m_sceneStack.push_back(scene);
	m_currentScene = scene;
}

void GameManager::PopCurrentScene()
{
	Scene* oldScene = m_sceneStack.back();
	m_sceneStack.pop_back();
	m_currentScene = m_sceneStack.back();
	delete oldScene;
}

void GameManager::Update()
{
	if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT))
	{
		if (glfwGetKey(GameManager::window, GLFW_KEY_T))
		{
			m_isDebug = false;
		}
	}
	else
	{
		if (glfwGetKey(GameManager::window, GLFW_KEY_T))
		{
			m_isDebug = true;
		}
	}
	

	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		m_currentScene->m_objects[i]->update();
	}

	m_currentScene->Update();

	DetectCollisions();
}

void GameManager::Draw()
{
	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		m_currentScene->m_objects[i]->Draw();
	}
}

void GameManager::DrawDebug()
{
	if (!m_isDebug)
	{
		return;
	}

	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		m_currentScene->m_objects[i]->DrawDebug();
	}
}

void GameManager::DetectCollisions()
{
	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		GameObject* first = m_currentScene->m_objects[i];
		if (first->m_collisionData->m_collisionMask == 0)
			continue;
		for (int p = 0; p < m_currentScene->m_objects.size(); p++)
		{
			if (i == p)
				continue;
			GameObject* second = m_currentScene->m_objects[p];
			if (first->m_collisionData->m_collisionMask & second->m_collisionData->m_collisionMask == 0)
				continue;
			if (CollisionData::AreColliding(CollisionData::CollisionDetectionType::AxisRealignedBoundingBox, first, second))
			{
				//TODO: This is slow as they are both going to check for collision against each other
				//there should be logic to prevent this
				first->onCollision(second);
			}
		}
	}
}

Scene::~Scene()
{
	delete &m_objects;
	delete &m_objectsDictionary;
}

void Scene::AddObject(GameObject* object)
{
	if (m_objectsDictionary.find(object->m_name) != m_objectsDictionary.end())
	{
		m_objects.push_back(object);
		m_objectsDictionary[object->m_name].push_back(object);
	}
	else {
		std::vector<GameObject*> objects;
		objects.push_back(object);
		m_objects.push_back(object);
		m_objectsDictionary[object->m_name] = objects;
	}
}

GameObject * Scene::GetObjectByName(std::string name)
{
	//TODO: Implement this function
	return nullptr;
}

std::vector<GameObject*> Scene::GetAllObjectsByName(std::string name)
{
	//TODO: IMPLEMENT this function
	return std::vector<GameObject*>();
}
