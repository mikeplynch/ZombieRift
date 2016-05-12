#include "Bullet.h"
#include "Player.h"
#include "Zombie.h"
#include "MainGameScene.h"

Bullet::Bullet()
{
}

Bullet::Bullet(GameObject* shooter, glm::vec3 dir, float maxDistance)
{
	m_name = "Bullet";
	CreateModel(m_name);
	m_model->GenCube(0.03f);
	EnableCollision();
	
	m_shooter = shooter;
	m_dir = dir;
	m_maxDistance = maxDistance;
}

Bullet::~Bullet()
{

}

void Bullet::onCollision(GameObject* other)
{
	if (other->m_name == "Zombie")
	{
		Player* player = static_cast<Player*>(m_shooter);
		Zombie* zombie = static_cast<Zombie*>(other);

		const int points = zombie->GetPoints();
		player->AddPoints(points);

		Delete();
		zombie->Delete();

		// Spawn more zombies
		MainGameScene* scene = static_cast<MainGameScene*>(GameManager::GetInstance()->m_currentScene);
		scene->AddZombies(player->GetScore(), points);
	}
}

void Bullet::CleanUp()
{
	m_speed = 0.0f;
	m_isAlive = false;
}

void Bullet::Update(float dt)
{
	m_translations += m_speed * m_dir;
	m_totalDistance += m_speed;

	if (m_totalDistance >= m_maxDistance)
	{
		Delete();
	}
}