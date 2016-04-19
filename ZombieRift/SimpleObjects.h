#pragma once
#include "GameManager.h"
#include "GameObject.h"

extern GLFWwindow* window;

class CubeObject : public GameObject {
public:
	CubeObject() { m_model->GenCube(1.0f); m_collisionData = new CollisionData(m_model);
	}

	CubeObject(float size) { m_model->GenCube(size); m_collisionData = new CollisionData(m_model);
	}

	void update() { };
};

class BoxObject : public GameObject {
public:
	BoxObject() { BoxObject(1.0f, 2.0f, 1.0f); }
	BoxObject(float length, float width, float height) { m_model->GenBox(length, width, height); m_collisionData = new CollisionData(m_model); }

	void update() { };
};

class PlayerBox : public BoxObject {
public:
	PlayerBox() { m_model->GenBox(1.0f, 2.0f, 1.0f); m_collisionData = new CollisionData(m_model); }
	void update()
	{
		SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT))
		{
			if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
			{
				m_transformations *= glm::translate(glm::vec3(0.0f, 0.0f, 0.01f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
			{
				m_transformations *= glm::translate(glm::vec3(0.0f, 0.0f, -0.01f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_Q))
			{
				m_transformations *= glm::rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_E))
			{
				m_transformations *= glm::rotate(1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
			}
		}
		else
		{
			if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT))
			{
				m_transformations *= glm::translate(glm::vec3(0.01f, 0.0f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_RIGHT))
			{
				m_transformations *= glm::translate(glm::vec3(-0.01f, 0.0f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
			{
				m_transformations *= glm::translate(glm::vec3(0.0f, 0.01f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
			{
				m_transformations *= glm::translate(glm::vec3(0.0f, -0.01f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_Q))
			{
				m_transformations *= glm::rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_E))
			{
				m_transformations *= glm::rotate(1.0f, glm::vec3(0.0f, 0.0f, -1.0f));
			}
		}
	}

	void onCollision(GameObject* other) {
		SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	}
};