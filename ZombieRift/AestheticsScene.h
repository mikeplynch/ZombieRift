#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"
#include "Automota.h"
#include "KinectUtilites.h"

class AestheticsScene : public Scene {
	Colony* colony;
	int counter = 0;
	KinectUtilities* kinect;

	virtual void Init();

	virtual void Update();
};