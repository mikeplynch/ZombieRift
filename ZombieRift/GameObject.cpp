#include "GameObject.h"

GameObject::GameObject()
{
	m_model = new Shape();
	m_worldCamera = Camera::GetInstance();
}

void GameObject::draw()
{
	m_model->RenderShape(m_transformations, m_worldCamera->GetView(), m_worldCamera->GetProjection(false));
}

CubeObject::CubeObject()
{
	m_model->GenCube(1.0f);
}
