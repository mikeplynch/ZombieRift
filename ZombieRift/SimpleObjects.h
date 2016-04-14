#pragma once
#include "GameObject.h"

class CubeObject : public GameObject {
public:
	CubeObject() { m_model->GenCube(1.0f); }

	void update() { };
};