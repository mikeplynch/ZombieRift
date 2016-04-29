#include "Player.h"
#include "GameManager.h"

static const float SPEED_MODIFIER = 10.0f;

Player::Player()
{
	m_model->GenBox(1.0f, 2.0f, 1.0f);
	m_collisionData = new CollisionData(m_model, this);
	m_worldCamera->ResetCamera();
	m_worldCamera->SetPositionAndTarget(m_translations, m_translations + m_worldCamera->GetForward());
	m_visible = false;
}

Player::~Player()
{
	if (m_collisionData != nullptr)
	{
		delete m_collisionData;
		m_collisionData = nullptr;
	}
}

void Player::Update()
{
	HandleInput();
	m_worldCamera->SetPositionAndTarget(m_translations, m_translations + m_worldCamera->GetForward());
}

void Player::HandleInput()
{
	float speed = m_moveSpeed;
	float degrees = 0.01f;

	if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(GameManager::window, GLFW_KEY_RIGHT_SHIFT))
	{
		speed *= SPEED_MODIFIER;
		degrees *= SPEED_MODIFIER;
	}

	if (glfwGetKey(GameManager::window, GLFW_KEY_A))
	{
		MoveSideways(-speed);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_D))
	{
		MoveSideways(speed);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_W))
	{
		MoveForward(speed);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_S))
	{
		MoveForward(-speed);
	}

	if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT))
	{
		ChangeLookYaw(degrees);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_RIGHT))
	{
		ChangeLookYaw(-degrees);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
	{
		ChangeLookPitch(-degrees);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
	{
		ChangeLookPitch(degrees);
	}
}

void Player::MoveSideways(float dist)
{
	glm::vec3 rightward = m_worldCamera->GetRightward();
	m_translations += dist * glm::vec3(rightward.x, 0.0f, rightward.z);
}

void Player::MoveVertical(float dist)
{
	// Nothing for now.
}

void Player::MoveForward(float dist)
{
	glm::vec3 forward = m_worldCamera->GetForward();
	m_translations += dist * glm::vec3(forward.x, 0.0f, forward.z);
}

void Player::ChangeLookPitch(float degrees)
{
	m_worldCamera->ChangePitch(degrees);
}

void Player::ChangeLookYaw(float degrees)
{
	m_worldCamera->ChangeYaw(degrees);
}

void Player::ChangeLookRoll(float degrees)
{
	m_worldCamera->ChangeRoll(degrees);
}