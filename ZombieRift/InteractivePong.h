#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"
#include "MeshGenerator.h"
#include "KinectUtilites.h"

class InteractivePong : public Scene {
	BoxObject* playerOne;
	BoxObject* playerTwo;
	BoxObject* ball;

	KinectUtilities* kinect;

	virtual void Init();

	virtual void Update(float dt);
};