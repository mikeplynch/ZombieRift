#include "GameManager.h"
#define DEBUG false

GameManager* GameManager::instance = nullptr;
GLFWwindow* GameManager::window = nullptr;

GameManager::GameManager()
{
}

bool GameManager::TestCollisions(GameObject* first, GameObject * second)
{
	bool areColliding = true;
	glm::vec3 min1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_min, 1.0f));
	glm::vec3 max1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_max, 1.0f));
	glm::vec3 min2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_min, 1.0f));
	glm::vec3 max2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_max, 1.0f));

	if (std::max(max1.x, min1.x) < std::min(min2.x, max2.x))
		areColliding = false;
	if (std::min(min1.x, max1.x) > std::max(max2.x, min2.x))
		areColliding = false;

	if (std::max(max1.y, min1.y) < std::min(min2.y, max2.y))
		areColliding = false;
	if (std::min(min1.y, max1.y) > std::max(max2.y, min2.y))
		areColliding = false;

	if (std::max(max1.z, min1.z) < std::min(min2.z, max2.z))
		areColliding = false;
	if (std::min(min1.z, max1.z) > std::max(max2.z, min2.z))
		areColliding = false;

	if (DEBUG && areColliding)
	{
		first->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	return areColliding;
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
				int secondElementSize = m_currentScene->m_objects[m_currentScene->m_objectNames[i]].size();
				for (int q = 0; q < secondElementSize; q++)
				{
					if (!(i == p && k == q))
					{
						if (TestCollisions(m_currentScene->m_objects[m_currentScene->m_objectNames[i]].at(k),
							m_currentScene->m_objects[m_currentScene->m_objectNames[p]].at(q)))
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
