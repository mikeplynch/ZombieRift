#include "BasicGun.h"

BasicGun::BasicGun()
{
}

BasicGun::~BasicGun()
{
}

BasicGun::BasicGun(GameObject* shooter)
{
	m_name = "BasicGun";
	CreateModel(m_name);
	m_model->GenBox(0.05f, 0.05f, 0.1f);
	SetColor(glm::vec3(0.0f, 0.0f, 0.0f));

	EnableCollision();
	m_collisionData->m_collisionMask = 0;

	m_shooter = shooter;
}

void BasicGun::Update(float dt)
{
}