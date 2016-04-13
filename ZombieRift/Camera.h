#pragma once

#include <glm\gtc\matrix_transform.hpp>
#include <SFML\Graphics.hpp>
#include <glm\gtx\quaternion.hpp>

class Camera {
private:
	//singleton class privates
	static Camera* instance;
	Camera();
	Camera(Camera const& other) {};
	Camera& operator=(Camera const& other) {};
	
	//Member variables for camera
	glm::vec3 m_vCameraPosition;
	glm::vec3 m_vCameraTarget;
	glm::vec3 m_vCameraUp;

	float m_fFov;
	float m_fAspectRatio;
	float m_fNearRenderDistance;
	float m_fFarRednerDistance;

	glm::quat targetAngle(glm::vec3 start, glm::vec3 end, float fIncrement);
	glm::vec3 getRight() { return glm::cross(getForward(), m_vCameraUp); }
	glm::vec3 getForward() { return m_vCameraTarget - m_vCameraPosition; }


public:
	//singleton class publics
	static Camera* GetInstance();
	static void ReleaseInstance();

	//Camera class Functions - (From assignment)
	
	//Gets the cameras view matrix
	glm::mat4 GetView() { return glm::lookAt(m_vCameraPosition, getForward() , m_vCameraUp); };

	//Get the cameras Project matrix.  Allows for the orthographic or the perspective matrix
	glm::mat4 GetProjection(bool bOrthographic);

	//Sets the camera's position
	void SetPosition(glm::vec3 v3Position) { m_vCameraPosition = v3Position; };

	//Sets the target of the Camera
	void SetTarget(glm::vec3 v3Target) { m_vCameraTarget = v3Target; };

	//Sets the up vector of the camera
	void SetUp(glm::vec3 v3Up) { m_vCameraUp = v3Up; };

	// Moves the camera forward or backward depending on the view vector
	void MoveForward(float fIncrement) { m_vCameraPosition += fIncrement * getForward(); };

	//Move the camera based on the right vector as determined by the View Vector
	void MoveSideways(float fIncrement) { m_vCameraPosition += fIncrement * getRight(); };

	// Move the camera up or down depending on the "up vector"
	void MoveVertical(float fIncrement) { m_vCameraPosition += fIncrement * m_vCameraUp; };

	//Orient the camera changing its angle in x
	void ChangePitch(float fIncrement);

	//Orient the camera changing its angle in z
	void ChangeRoll(float fIncrement);

	//Orient the camera changing its angle in y
	void ChangeYaw(float fIncrement);
};