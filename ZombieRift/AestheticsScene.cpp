#include "AestheticsScene.h"

void AestheticsScene::Init()
{
	glClearColor(0, 0, 0, 0);
	colony = new Colony(1, 100, 100);
	//colony->RandomizeState(80);
	colony->AddToScene(this);
	int tries = 0;
	while ((kinect = KinectUtilities::GetInstance()) == nullptr || tries > 100) {
		tries++;
		fprintf(stderr, "Attempting to initializse the kinect...\n");
	}
	colony->worldPosition = glm::vec3(0, 0, -20);

	lowX = 0;
	highX = 0;
	lowY = 0; 
	highY = 0;
	lowZ = 0;
	highZ = 0;
}

void AestheticsScene::Update()
{
	counter++;
	if (counter % 5 == 0)
		colony->Update();
	//if (counter % 500 == 0)
	//	colony->RandomizeState(80);

	if (kinect != nullptr) {
		kinect->GetKinectData();
		if (kinect->m_tracked)
		{
			//Right hand
			const CameraSpacePoint& rightHand = kinect->joints[JointType_HandRight].Position;
			//colony->worldPosition = glm::vec3(rightHand.X, rightHand.Y, -20.0f);
			if (rightHand.X > highX) highX = rightHand.X;
			if (rightHand.X < lowX) lowX= rightHand.X;
			if (rightHand.Y > highY) highY = rightHand.Y;
			if (rightHand.Y < lowY) lowY = rightHand.Y;
			if (rightHand.Z > highZ) highZ = rightHand.Z;
			if (rightHand.Z < lowZ) lowZ = rightHand.X;

			int xCoord = round(MapRange(rightHand.X, lowX, highX, 0, (float)colony->width - 1));
			int yCoord = round(MapRange(rightHand.Y, lowY, highY, 0, (float)colony->height - 1));
			int zCoord = round(MapRange(rightHand.Z, lowZ, highZ, 0, (float)colony->length - 1));

			colony->cells[xCoord][yCoord][zCoord]->m_state = 1;
			colony->cells[xCoord][yCoord][zCoord]->m_nextState = 1;

			//Left hand
			const CameraSpacePoint& leftHand = kinect->joints[JointType_HandLeft].Position;
			//colony->worldPosition = glm::vec3(rightHand.X, rightHand.Y, -20.0f);
			if (leftHand.X > highX) highX = leftHand.X;
			if (leftHand.X < lowX) lowX = leftHand.X;
			if (leftHand.Y > highY) highY = leftHand.Y;
			if (leftHand.Y < lowY) lowY = leftHand.Y;
			if (leftHand.Z > highZ) highZ = leftHand.Z;
			if (leftHand.Z < lowZ) lowZ = leftHand.X;

			xCoord = round(MapRange(leftHand.X, lowX, highX, 0, (float)colony->width - 1));
			yCoord = round(MapRange(leftHand.Y, lowY, highY, 0, (float)colony->height - 1));
			zCoord = round(MapRange(leftHand.Z, lowZ, highZ, 0, (float)colony->length - 1));

			colony->cells[xCoord][yCoord][zCoord]->m_state = 1;
			colony->cells[xCoord][yCoord][zCoord]->m_nextState = 1;
		}
		/*int last = 0;
		for (int i = 0; i < 512 * 424; ) {
			int index = round(MapRange(i, 0, 512 * 424, 0, colony->width * colony->height));
			last = index;
			float depth = kinect->depth2xyz[index].Z;
			if (depth < 0)
			{
				depth = 3;
			}
			//depth += 2;
			depth *= 3;
			int h = round(colony->height / index);
			int w = colony->length % index;
			colony->cells[h][w][0]->m_translations += glm::vec3(0, 0, -depth);
			colony->cells[h][w][0]->m_nextState = 1;
			colony->cells[h][w][0]->m_state = 1;

			i += (index - last);

		}
		for (int h = 0; h < colony->height; h++)
		{
			for (int w = 0; w < colony->width; w++)
			{
				for (int l = 0; l < colony->length; l++)
				{
					int index = round(MapRange(h * w, 0, colony->width * colony->height, 0, 512 * 424));
					float depth = kinect->depth2xyz[index].Z;
					if (depth < 0)
					{
						depth = 3;
					}
					//depth += 2;
					depth *= 3;
					colony->cells[h][w][l]->m_translations += glm::vec3(0, 0, -depth);
					colony->cells[h][w][l]->m_nextState = 1;
					colony->cells[h][w][l]->m_state = 1;

				}
			}
		}*/
	}
}

float AestheticsScene::MapRange(float value, float low1, float high1, float low2, float high2)
{
	return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
}
