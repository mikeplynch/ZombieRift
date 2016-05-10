#include "Bouncing.h"

void Bouncing::Init()
{
	ball = new GravityObject(1.0f, 1.0f);
	AddObject(ball);
	
}

void Bouncing::Update(float dt)
{
	
}
