#include "InputManager.h"
#include <Windows.h>
#include <iostream>
#include "../XLEngine/XLUtility.h"
#include "Camera.h"
#include "Timer.h"
#include "Resources.h"

using namespace XL::Utility;
using namespace XL::GamePlay;

XL::GamePlay::KeyCode XL::GamePlay::InputManager::keycode;
float XL::GamePlay::InputManager::mouseX;
float XL::GamePlay::InputManager::mouseY;
float XL::GamePlay::InputManager::newMouseX;
float XL::GamePlay::InputManager::newMouseY;
float XL::GamePlay::InputManager::prevMouseX;
float XL::GamePlay::InputManager::prevMouseY;
float XL::GamePlay::InputManager::originX;
float XL::GamePlay::InputManager::originY;
const float cameraSpeed = 2.0f;

void XL::GamePlay::InputManager::Update()
{
	ProcessMovement();
	ProcessMouseLook();
}

void XL::GamePlay::InputManager::ProcessMovement()
{
	XMFLOAT3 movement{ 0.0f, 0.0f, 0.0f };

	if (GetAsyncKeyState('W')) movement.z += cameraSpeed * Timer::deltaTime;
	if (GetAsyncKeyState('S')) movement.z -= cameraSpeed * Timer::deltaTime;
	if (GetAsyncKeyState('A')) movement.x -= cameraSpeed * Timer::deltaTime;
	if (GetAsyncKeyState('D')) movement.x += cameraSpeed * Timer::deltaTime;
	if (GetAsyncKeyState('E')) movement.y += cameraSpeed * Timer::deltaTime;
	if (GetAsyncKeyState('Q')) movement.y -= cameraSpeed * Timer::deltaTime;

	Camera::Translate(movement.x, movement.y, movement.z);
}

void XL::GamePlay::InputManager::ProcessMouseLook()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)  // 마우스 우클릭 처음 눌렀을 때
	{
		originX = mouseX;
		originY = mouseY;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)  // 마우스 우클릭 유지 중
	{
		float deltaX = (originX - mouseX) / XL::Graphics::D3D11::Resources::GetInstance().ScreenWidth;
		float deltaY = (originY - mouseY) / XL::Graphics::D3D11::Resources::GetInstance().ScreenHeight;

		Camera::SetDirection(5 * deltaY * Timer::deltaTime, 5 * deltaX * Timer::deltaTime, 0.0f);

		Debug::Log(mouseX);
		Debug::Log(mouseY);
	}
}
// todo: 부드러운 움직임 아닐 수 있도록
// todo: 키보드로 조작했다가 마우스를 돌리면 가까이 와짐
