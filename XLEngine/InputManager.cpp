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
const float cameraSpeed = 2.0f;

void XL::GamePlay::InputManager::Update()
{
	if (GetAsyncKeyState('W'))		// W
	{
		Camera::Translate(0.0f, 0.0f, cameraSpeed * Timer::deltaTime);
		//Debug::Log("w down");
	}

	if (GetAsyncKeyState('S'))		// S
	{
		Camera::Translate(0.0f, 0.0f, -cameraSpeed * Timer::deltaTime);
		//Debug::Log("s down");
	}

	if (GetAsyncKeyState('A'))		// A
	{
		Camera::Translate(-cameraSpeed * Timer::deltaTime, 0.0f, 0.0f);
		//Debug::Log("a down");
	}

	if (GetAsyncKeyState('D'))		// D
	{
		Camera::Translate(cameraSpeed * Timer::deltaTime, 0.0f, 0.0f);
		//Debug::Log("d down");
	}

	if (GetAsyncKeyState('E'))		// E
	{
		Camera::Translate(0.0f, cameraSpeed * Timer::deltaTime, 0.0f);
		//Debug::Log("a down");
	}

	if (GetAsyncKeyState('Q'))		// Q
	{
		Camera::Translate(0.0f, -cameraSpeed * Timer::deltaTime, 0.0f);
		//Debug::Log("d down");
	}

	// todo: Lbutton을 찍었을 때를 기준으로 움직일 수 있도록 수정할 것
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		newMouseX = (mouseX - XL::Graphics::D3D11::Resources::GetInstance().ScreenWidth / 2) / XL::Graphics::D3D11::Resources::GetInstance().ScreenWidth;
		newMouseY = (mouseY - XL::Graphics::D3D11::Resources::GetInstance().ScreenHeight / 2) / XL::Graphics::D3D11::Resources::GetInstance().ScreenHeight;
	
		float deltaX = newMouseX - prevMouseX;
		float deltaY = newMouseY - prevMouseY;

		Debug::Log(deltaX);
		Debug::Log(deltaY);


		Camera::SetDirection(deltaX, deltaY, 0.0f);

		prevMouseX = newMouseX;
		prevMouseY = newMouseY;
	}


}

void XL::GamePlay::InputManager::Mouse()
{

}
