#include "AestheticsScene.h"

void AestheticsScene::Init()
{
	colony = new Colony(5, 5, 5);
	colony->RandomizeState(80);
	colony->AddToScene(this);
	int tries = 0;
	while ((kinect = KinectUtilities::GetInstance()) == nullptr || tries > 100) {
		tries++;
		fprintf(stderr, "Attempting to initializse the kinect...\n");
	}
}

void AestheticsScene::Update()
{
	counter++;
	if (counter % 20 == 0)
		colony->Update();
	if (counter % 100 == 0)
		colony->RandomizeState(80);

	if (kinect != nullptr) {
		kinect->GetKinectData();
		if (kinect->m_tracked)
		{
			const CameraSpacePoint& rightHand = kinect->joints[JointType_HandRight].Position;
			colony->worldPosition = glm::vec3(rightHand.X, rightHand.Y, rightHand.Z);
			for (int i = 0; i < JointType_Count; i++)
			{
				if (kinect->joints[i].Position.X > 0)
				{
					printf("something happend!");
				}
			}
		}
	}
}
