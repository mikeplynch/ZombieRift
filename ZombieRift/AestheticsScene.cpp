#include "AestheticsScene.h"

void AestheticsScene::Init()
{
	colony = Colony(5, 5, 5);
	colony.RandomizeState(80);
	colony.AddToScene(this);
}

void AestheticsScene::Update()
{
	counter++;
	if (counter % 100 == 0)
		colony.Update();
	if (counter % 3000 == 0)
		colony.RandomizeState(80);
}
