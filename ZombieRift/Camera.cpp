#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera()
{
	//Set up initial camera values
	m_fFov = 45.0f;
	m_fAspectRatio = 1080.0f / 768.0f;
	m_fNearRenderDistance = 0.01f;
	m_fFarRednerDistance = 1000.0f;
	m_vCameraPosition = glm::vec3(1, 0, 0);
	m_vCameraUp = glm::vec3(0, 1, 0);
	m_vCameraTarget = glm::vec3(0, 0, 0);
}

glm::quat Camera::targetAngle(glm::vec3 start,glm::vec3 end, float fIncrement)
{
	start = glm::normalize(start);
	end = glm::normalize(end);

	//Rotate on the 'x' of the camera.
	start *= 90;
	glm::quat startAngle = glm::quat(start);

	//Need to make an angle for 'right' which is the camera's right value
	end /= 1;
	end *= 90;
	glm::quat endAngle = glm::quat(end);

	//Now figure out the desired rotation
	return glm::mix(startAngle, endAngle, fIncrement);
}

Camera * Camera::GetInstance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else 
	{
		return instance = new Camera();
	}
}

void Camera::ReleaseInstance()
{
	if (instance != nullptr) 
	{
		delete instance;
		instance = nullptr;
	}
}

glm::mat4 Camera::GetProjection(bool bOrthographic)
{
	return bOrthographic ?
		glm::ortho(-384.0f, 384.0f, -540.0f, 540.0f) :
		glm::perspective(m_fFov, m_fAspectRatio, m_fNearRenderDistance, m_fFarRednerDistance);
}

void Camera::ChangePitch(float fIncrement)
{
	/*
	//Get the desired rotation angle
	glm::quat angle = targetAngle(getForward() , m_vCameraUp, fIncrement);
	glm::vec3 normalAngle = glm::eulerAngles(angle);
	m_vCameraUp = glm::normalize(glm::rotate(m_vCameraUp, 90.0f, glm::normalize(normalAngle)));
	glm::vec3 forwardVector = glm::normalize(glm::rotate(getForward(), 90.0f, glm::normalize(normalAngle)));
	m_vCameraTarget += forwardVector;*/
}

void Camera::ChangeRoll(float fIncrement)
{
	/*
	//The target vectors for this start at camera and end at the oposite of camera
	glm::quat angle = targetAngle(m_vCameraUp, getRight(), fIncrement);
	glm::vec3 normalAngle = glm::eulerAngles(angle);
	m_vCameraUp = glm::normalize(glm::rotate(m_vCameraUp, 90.0f, glm::normalize(normalAngle)));
	*/
}

void Camera::ChangeYaw(float fIncrement)
{
	/*
	//The target vectors for this start at camera and end at the oposite of camera
	glm::quat angle = targetAngle(getForward(), getRight(), fIncrement);
	glm::vec3 normalAngle = glm::eulerAngles(angle);
	//m_vCameraTarget += glm::rotate(m_vCameraTarget, 90.0f, glm::normalize(normalAngle));
	*/
}
