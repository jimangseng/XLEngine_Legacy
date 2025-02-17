#include "Game.h"

#include "../XLEngine/XLEngine.h"
#include "../XLEngine/Cube.h"
#include "../XLEngine/Timer.h"
#include <iostream>
#include "../XLEngine/Camera.h"

using namespace XL::GamePlay;
using namespace XL::Math;
using namespace XL::GameObjects;

void Game::Start()
{
	Cube cube1;
	cube1.size = 0.8f;
	cube1.Translate(0.0f, 0.0f, 0.0f);
	scene.AddObject(cube1);

	Cube cube2;
	cube2.size = 0.4f;
	cube2.Translate(0.0f, 0.0f, 5.0f);
	scene.AddObject(cube2);
}

void Game::Update()
{
	//std::cout << Timer::deltaTime << std::endl;
	//std::cout << Timer::frateRate << std::endl;
	//std::cout << Timer::time << std::endl << std::endl;

	// todo: ��ũ��Ʈ �и� �� ��ü�� ���� �ǵ��� ��� �ؾ� �ϴ°�?

	//scene.GetObject(0)->SetPosition(0.05f * sin(Timer::time * Timer::deltaTime), 0.0f, 0.0f);
	scene.GetObject(0)->Rotate(0.0f, -0.5f * Timer::deltaTime, 0.0f);
	scene.GetObject(1)->Rotate(1.5f * Timer::deltaTime, 0.0f, 1.5f * Timer::deltaTime);
}

void Game::Finish()
{

}