#include "AestheticsScene.h"

void AestheticsScene::Init()
{
	colony = new Colony(5, 5, 5);
	colony->RandomizeState(80);
	colony->AddToScene(this);
}

void AestheticsScene::Update()
{
	counter++;
	if (counter % 20 == 0)
		colony->Update();
	if (counter % 1000 == 0)
		colony->RandomizeState(80);
}
