#include "Camera.h"
#include "InputManager.h"
#include "Timer.h"

XMMATRIX XL::Camera::viewMatrix = XMMatrixIdentity();
XMMATRIX XL::Camera::cameraTranslation = XMMatrixIdentity();
XMVECTOR XL::Camera::position = { 0.0f, 0.0f, -3.0f };
XMVECTOR XL::Camera::direction = { 0.0f, 0.0f, 1.0f };

XL::Camera::Camera()
{
	viewMatrix = XMMatrixLookToLH(position, direction, XMVECTOR{ 0.0f, 1.0f, 0.0f });
}

void XL::Camera::Update()
{
	viewMatrix = XMMatrixLookToLH(position, direction, XMVECTOR{ 0.0f, 1.0f, 0.0f });
}

void XL::Camera::Translate(float x, float y, float z)
{
	position += { x, y, z};
}

void XL::Camera::SetDirection(float x, float y, float z)
{
	direction += {-x, y, z};
	direction = XMVector3Normalize(direction);
}
