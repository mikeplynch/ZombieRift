#include "Player.h"
#include "GameManager.h"

static const float SPEED_MODIFIER = 10.0f;

Player::Player()
{
	m_name = "Player";
	CreateModel(m_name);
	m_model->GenBox(1.0f, 2.0f, 1.0f);
	EnableCollision();
	m_worldCamera->ResetCamera();
	m_worldCamera->SetPositionAndTarget(m_translations, m_translations + m_worldCamera->GetForward());
	m_bullets = std::vector<Bullet*>();

	m_gun = new BasicGun(this);
	m_gun->m_translations = m_translations + (0.1f * m_worldCamera->GetForward()) + glm::vec3(0.05f, -0.05f, 0.0f);

	m_reticle = new SphereObject(0.00005f);
	m_reticle->m_collisionData->m_collisionMask = 0;
	m_reticle->SetColor(glm::vec3(255/255.0f, 100/255.0f, 120/255.0f));
	m_reticle->m_translations = m_translations + (0.01f * m_worldCamera->GetForward());

	m_visible = false;
}

Player::~Player()
{
	if (m_collisionData != nullptr)
	{
		delete m_collisionData;
		m_collisionData = nullptr;
	}

	ClearBullets();
}

void Player::ClearBullets()
{
	for (std::vector<Bullet*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); iter++)
	{
		if (*iter != nullptr)
		{
			delete (*iter);
		}
	}

	m_bullets.clear();
}

void Player::Update(float dt)
{
	HandleInput(dt);
	//glm::vec3 behind = glm::vec3(m_translations.x, m_translations.y, m_translations.z + 5); //TC - Don't remove this please
	//m_worldCamera->SetPositionAndTarget(m_translations, m_translations + m_worldCamera->GetForward());
	//m_worldCamera->SetPosition(m_translations);
	//m_reticle->m_translations = m_translations + (0.01f * m_worldCamera->GetForward());
	CheckBullets();

	std::cout << "Score: " << m_score << std::endl;
}

void Player::onCollision(GameObject* other)
{
	
}

void Player::HandleInput(float dt)
{
	float speed = m_moveSpeed * dt;
	float reticleSpeed = m_reticleSpeed * dt;
	float degrees = 0.1f;

	if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(GameManager::window, GLFW_KEY_RIGHT_SHIFT))
	{
		speed *= SPEED_MODIFIER;
		degrees *= SPEED_MODIFIER;

	}

	// For now, we don't want player movement.
	/*if (glfwGetKey(GameManager::window, GLFW_KEY_A))
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
	}*/
	

	/* Looking around */
	if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT))
	{
		//ChangeLookYaw(degrees);
		ChangeAimHorizontal(-reticleSpeed);
		//m_reticle->m_translations += glm::vec3(-reticleSpeed, 0.0f, 0.0f);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_RIGHT))
	{
		ChangeAimHorizontal(reticleSpeed);
		//ChangeLookYaw(-degrees);
		//m_reticle->m_translations += glm::vec3(reticleSpeed, 0.0f, 0.0f);

	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
	{
		ChangeAimVertical(-reticleSpeed);
		//ChangeLookPitch(-degrees);
		//m_reticle->m_translations += glm::vec3(0.0f, -reticleSpeed, 0.0f);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
	{
		ChangeAimVertical(reticleSpeed);
		//ChangeLookPitch(degrees);
		//m_reticle->m_translations += glm::vec3(0.0f, reticleSpeed, 0.0f);
	}

	if (glfwGetKey(GameManager::window, GLFW_KEY_SPACE))
	{
		if (m_canShoot)
		{
			Shoot();
		}

		m_canShoot = false;
	}
	else
	{
		m_canShoot = true;
	}
}

void Player::Shoot()
{
	glm::vec3 direction = glm::normalize(m_reticle->m_translations - m_translations);
	float farDistance = m_worldCamera->GetNearFarPlanes().y;
	Bullet* bullet = new Bullet(this, direction, farDistance / 10);
	bullet->m_translations = m_gun->m_translations; //+(0.0f * m_worldCamera->GetForward());

	GameManager::GetInstance()->m_currentScene->AddObject(bullet);
	m_bullets.push_back(bullet);
}

void Player::CheckBullets()
{
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets.at(i) == nullptr)
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}

void Player::AddPoints(int points)
{
	m_score += points;
}

void Player::ChangeAimHorizontal(float dist)
{
	m_reticle->m_translations += glm::vec3(dist, 0.0f, 0.0f);
	m_gun->m_rotations *= glm::rotate(-dist * 5000, glm::vec3(0.0f, 1.0f, 0.0f));

}

void Player::ChangeAimVertical(float dist)
{
	m_reticle->m_translations += glm::vec3(0.0f, dist, 0.0f);
	m_gun->m_rotations *= glm::rotate(dist * 5000, glm::vec3(1.0f, 0.0f, 0.0f));
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
	m_rotations *= glm::rotate(degrees, glm::vec3(0.0f, 1.0f, 0.0f));
	m_worldCamera->ChangeYaw(degrees);
}

void Player::ChangeLookRoll(float degrees)
{
	m_worldCamera->ChangeRoll(degrees);
}