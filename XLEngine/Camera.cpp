#include "Camera.h"

XMMATRIX XL::Camera::viewMatrix = XMMatrixIdentity();

XL::Camera::Camera()
	:position{0.0f, 3.0f, -3.0f}, target{0.0f, 0.0f, 0.0f}
{
	viewMatrix = XMMatrixLookAtLH(position, target, XMVECTOR{ 0.0f, 1.0f, 0.0f});
}
