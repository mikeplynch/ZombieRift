#pragma once

#include "GameObject.h"
#include "CollisionData.h"

class Scene {
public:
	Scene() { };
	~Scene();
	std::map<std::string, std::vector<GameObject*>> m_objectsDictionary;
	std::vector<GameObject*> m_objects;
	bool initialized = false;

	virtual void Init() = 0;

	virtual void Update() = 0;

	void AddObject(GameObject* object);

	GameObject* GetObjectByName(std::string name);
	std::vector<GameObject*> GetAllObjectsByName(std::string name);
};

class GameManager {
private:
	bool m_isDebug = false;

	static GameManager* instance;
	GameManager();
	GameManager(GameManager const* other) {};
	GameManager& operator=(GameManager const& other) {};
public:
	static GameManager* GetInstance();
	static void ReleaseInstance();

	static GLFWwindow* window;

	std::vector<Scene*> m_sceneStack;
	Scene* m_currentScene;

	void SetCurrentScene(Scene* scene);
	void PopCurrentScene();

	///void Update(float deltaTime);
	void Update();

	void Draw();
	void DrawDebug();

	void DetectCollisions();
};