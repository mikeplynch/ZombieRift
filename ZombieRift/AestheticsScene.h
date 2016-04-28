#pragma once
#include "GameManager.h"
#include "Automota.h"

class AestheticsScene : public Scene {
	Colony colony;
	int counter = 0;

	virtual void Init();

	virtual void Update();
};