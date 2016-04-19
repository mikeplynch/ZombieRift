#pragma once

#include "GameObject.h"

class Scene {
public:
	Scene() { init(); }
	~Scene();
	std::map<std::string, std::vector<GameObject*>> m_objects;
	std::vector<std::string> m_objectNames;

	virtual void init() { };

	virtual void Update() {};

	void AddObject(GameObject* object);

	GameObject* GetObjectByName(std::string name);
	std::vector<GameObject*> GetAllObjectsByName(std::string name);
};

class GameManager {
private:
	static GameManager* instance;
	GameManager();
	GameManager(GameManager const* other) {};
	GameManager& operator=(GameManager const& other) {};
	bool TestCollisions(GameObject* first, GameObject* second);
public:
	static GameManager* GetInstance();
	static void ReleaseInstance();

	static GLFWwindow* window;

	std::vector<Scene*> m_sceneStack;
	Scene* m_currentScene;

	void SetCurrentScene(Scene* scene);
	void PopCurrentScene();

	void Update();

	void Draw();

	void DetectCollisions();
};