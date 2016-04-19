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
	for (int i = 0; i < m_currentScene->m_objectNames.size(); i++)
	{
		int elementSize = m_currentScene->m_objects[m_currentScene->m_objectNames[i]].size();
		for (int k = 0; k < elementSize; k++)
		{
			m_currentScene->m_objects[m_currentScene->m_objectNames[i]].at(k)->update();
		}
	}

	m_currentScene->Update();

	DetectCollisions();
}

void GameManager::Draw()
{
	for (int i = 0; i < m_currentScene->m_objectNames.size(); i++)
	{
		int elementSize = m_currentScene->m_objects[m_currentScene->m_objectNames[i]].size();
			for (int k = 0; k < elementSize; k++)
			{
				m_currentScene->m_objects[m_currentScene->m_objectNames[i]].at(k)->draw();
			}
	}
}

void GameManager::DetectCollisions()
{
	for (int i = 0; i < m_currentScene->m_objectNames.size(); i++)
	{
		int elementSize = m_currentScene->m_objects[m_currentScene->m_objectNames[i]].size();
		for (int k = 0; k < elementSize; k++)
		{
			for (int p = 0; p < m_currentScene->m_objectNames.size(); p++)
			{
				GameObject* first = m_currentScene->m_objects[m_currentScene->m_objectNames[i]].at(k);
				if (first->m_collisionData->m_collisionMask == 0)
					continue;
				int secondElementSize = m_currentScene->m_objects[m_currentScene->m_objectNames[i]].size();
				for (int q = 0; q < secondElementSize; q++)
				{
					if (i == p && k == q)
						continue;
					GameObject* second = m_currentScene->m_objects[m_currentScene->m_objectNames[p]].at(q);
					if (first->m_collisionData->m_collisionMask & second->m_collisionData->m_collisionMask == 0)
						continue;
					if (CollisionData::AreColliding(first, second))
					{
						//TODO: This is slow as they are both going to check for collision against each other
						//there should be logic to prevent this
						m_currentScene->m_objects[m_currentScene->m_objectNames[p]].at(q)->onCollision(m_currentScene->m_objects[m_currentScene->m_objectNames[p]].at(q));
					}	
				}
			}
		}
	}
}

Scene::~Scene()
{
	delete &m_objectNames;
	delete &m_objects;
}

void Scene::AddObject(GameObject* object)
{
	if (m_objects.find(object->m_name) != m_objects.end())
	{
		m_objectNames.push_back(object->m_name);
		m_objects[object->m_name].push_back(object);
	}
	else {
		std::vector<GameObject*> objects;
		objects.push_back(object);
		m_objectNames.push_back(object->m_name);
		m_objects[object->m_name] = objects;
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
