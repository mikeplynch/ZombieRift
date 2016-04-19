#include "GameObject.h"

GameObject::GameObject()
{
	m_worldCamera = Camera::GetInstance();
	m_data = new std::map<std::string, int>();
	m_model = new Shape();
	m_collisionData = nullptr;
}

GameObject::~GameObject()
{
	delete m_model;
	m_model = nullptr;
	delete m_data;
	m_data = nullptr;
	m_worldCamera = nullptr;
}

void GameObject::SetModel(Shape* shape)
{
	if (m_model != nullptr)
	{
		delete m_model;
	}
	m_model = shape; 
	if (m_model != nullptr)
	{
		delete m_collisionData;
	}
	m_collisionData = new CollisionData(shape);
}

void GameObject::draw()
{
	m_model->RenderShape(m_transformations, m_worldCamera->GetView(), m_worldCamera->GetProjection(false));
}