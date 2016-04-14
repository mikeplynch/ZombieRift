#include "GameObject.h"

GameObject::GameObject()
{
	m_model = new Shape();
	m_worldCamera = Camera::GetInstance();
	m_data = new std::map<std::string, int>();
}

GameObject::~GameObject()
{
	delete m_model;
	m_model = nullptr;
	delete m_data;
	m_data = nullptr;
	m_worldCamera = nullptr;
}

void GameObject::draw()
{
	m_model->RenderShape(m_transformations, m_worldCamera->GetView(), m_worldCamera->GetProjection(false));
}