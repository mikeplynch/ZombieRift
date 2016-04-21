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
	if (m_model != nullptr)
	{
		delete m_model;
		m_model = nullptr;
	}
	if (m_data != nullptr)
	{
		delete m_data;
		m_data = nullptr;
	}

	if (m_worldCamera != nullptr)
	{
		//delete m_worldCamera;
		m_worldCamera = nullptr;
	}
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
	m_collisionData = new CollisionData(shape, this);
}

void GameObject::Draw()
{
	m_transformations = glm::mat4(1.0f);
	m_transformations *= glm::translate(m_translations);
	m_transformations *= m_rotations;
	m_transformations *= glm::scale(m_scales);
	m_model->RenderShape(m_transformations, m_worldCamera->GetView(), m_worldCamera->GetProjection(false));
}

void GameObject::DrawDebug()
{
	//The reason this wraps only one function is for future additions of drawing 
	//vector information and any other possible information.
	m_collisionData->DrawBoundingBox();
}