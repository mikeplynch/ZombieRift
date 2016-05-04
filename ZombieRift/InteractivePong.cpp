#include "InteractivePong.h"

void InteractivePong::Init()
{
	playerOne = new BoxObject(2.0f, 1.0f, 1.0f);
	//playerOne->m_scales = glm::vec3(2.0f, 1.0f, 1.0f);
	playerOne->m_translations = glm::vec3(-10.0f, 0.0f, 0.0f);
	playerOne->m_name = "PlayerOne";
	AddObject(playerOne);

	playerTwo = new BoxObject(2.0f, 1.0f, 1.0f);
	//playerTwo->m_scales = glm::vec3(2.0f, 1.0f, 1.0f);
	playerTwo->m_translations = glm::vec3(-10.0f, 0.0f, 0.0f);
	playerTwo->m_name = "PlayerTwo";
	AddObject(playerTwo);

	ball = new BoxObject();
	Model* sphere = new Model("Sphere");
	sphere->GenSphere(2.0f, 6);
	ball->SetModel(sphere);
	AddObject(ball);

	int tries = 0;
	while ((kinect = KinectUtilities::GetInstance()) == nullptr || tries > 100) {
		tries++;
		fprintf(stderr, "Attempting to initializse the kinect...\n");
	}
}

void InteractivePong::Update()
{
	if (kinect != nullptr)
	{
		kinect->GetKinectData();
		std::cout << kinect->depth2xyz[10].Z << std::endl;
	}
}
