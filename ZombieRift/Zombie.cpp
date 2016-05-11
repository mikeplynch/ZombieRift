#include "Zombie.h"
#include "GameManager.h"
#include "Player.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
	if (m_collisionData != nullptr)
	{
		delete m_collisionData;
		m_collisionData = nullptr;
	}
}

Zombie::Zombie(glm::vec3 position, glm::vec3 target)
{
	m_name = "Zombie";
	CreateModel(m_name);
	m_model->GenBox(1.0f, 2.0f, 1.0f);
	SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	EnableCollision();

	m_translations = position;
	m_target = target;
}

void Zombie::Update(float dt)
{
	m_translations += glm::normalize(m_target - m_translations) * m_moveSpeed * dt;
}

void Zombie::onCollision(GameObject* other)
{
	if (other->m_name == "Player")
	{
		Player* player = static_cast<Player*>(other);

		// Lose state
		// Either show a game over, restart, lose health, something...
		SetColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Sets the zombie to be red for now.
	}
}

void Zombie::CleanUp()
{
	m_points = 0;
	m_moveSpeed = 0.0f;
}