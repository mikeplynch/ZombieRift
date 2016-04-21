#pragma once
#include "GameManager.h"
#include "GameObject.h"

extern GLFWwindow* window;

class CubeObject : public GameObject {
public:
	CubeObject() { m_model->GenCube(1.0f); m_collisionData = new CollisionData(m_model, this);}

	CubeObject(float size) { m_model->GenCube(size); m_collisionData = new CollisionData(m_model, this); }

	void update() 
	{
		m_collisionData->UpdateBoundingBoxes();
	};
};

class BoxObject : public GameObject {
public:
	BoxObject() { BoxObject(1.0f, 2.0f, 1.0f); }
	BoxObject(float length, float width, float height) { m_model->GenBox(length, width, height); m_collisionData = new CollisionData(m_model, this);  }

	void update() 
	{
		//TODO: Discuss whether or not calling this should be an "option" of those inheriting form GameObject
		m_collisionData->UpdateBoundingBoxes();
	};
};

class PlayerBox : public BoxObject {
public:
	PlayerBox() { m_model->GenBox(1.0f, 2.0f, 1.0f); m_collisionData = new CollisionData(m_model, this);}
	void update()
	{
		m_collisionData->UpdateBoundingBoxes();
		SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT))
		{
			if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
			{
				m_translations += glm::vec3(0.0f, -0.1f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
			{
				m_translations += glm::vec3(0.0f, 0.1f, 0.01f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_Q))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_E))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			}
		}
		else
		{
			if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT))
			{
				m_translations += glm::vec3(-0.1f, 0.0f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_RIGHT))
			{
				m_translations += glm::vec3(0.1f, 0.0f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
			{
				m_translations += glm::vec3(0.0f, 0.1f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
			{
				m_translations += glm::vec3(0.0f, -0.1f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_Q))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_E))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, 0.0f, -1.0f));
			}
		}

		// Generate the realigned bounding box
		//TODO: FIX THIS! THIS IS VERY BAD - TC 4/20
		//delete m_reBoundingBox;
		//m_reBoundingBox = new Shape();
		//m_reBoundingBox->GenBox(m_collisionData->m_reBoundingPoints);
	}

	void onCollision(GameObject* other) {
		SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	}
};