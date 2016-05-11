#include "Bullet.h"
#include "Player.h"
#include "Zombie.h"
#include "A10Scene.h"

Bullet::Bullet()
{
}

Bullet::Bullet(GameObject* shooter, glm::vec3 dir, float maxDistance)
{
	m_name = "Bullet";
	CreateModel(m_name);
	m_model->GenCube(0.1f);
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

		int points = zombie->GetPoints();
		player->AddPoints(points);

		Delete();
		zombie->Delete();

		// Spawn more zombies
		MainGameScene* scene = static_cast<MainGameScene*>(GameManager::GetInstance()->m_currentScene);

		// There is a bug with this right now. I think I need to queue it to happen next frame. - TC
		//scene->AddZombies(player->GetScore(), points);
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