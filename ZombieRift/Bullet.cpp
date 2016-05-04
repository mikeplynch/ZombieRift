#include "Bullet.h"

Bullet::Bullet()
{
	m_name = "Bullet";
	CreateModel(m_name);
	m_model->GenCube(0.1f);
	EnableCollision();

	m_dir = glm::vec3(0.0f);
	m_maxDistance = 1000.0f;
}

Bullet::Bullet(glm::vec3 dir, float maxDistance)
{
	m_name = "Bullet";
	CreateModel(m_name);
	m_model->GenCube(0.1f);
	EnableCollision();

	m_dir = dir;
	m_maxDistance = maxDistance;
}

Bullet::~Bullet()
{

}

void Bullet::onCollision(GameObject* other)
{
	if (other->m_name != "Player" && other->m_name != "Bullet")
	{
		DisableBullet();
	}
}

void Bullet::DisableBullet()
{
	m_speed = 0.0f;
	m_isAlive = false;

	m_visible = false;
	m_collisionData->m_collisionMask = 0;
}

void Bullet::Update(float dt)
{
	m_translations += m_speed * m_dir;
	m_totalDistance += m_speed;

	if (m_totalDistance >= m_maxDistance)
	{
		DisableBullet();
	}
}