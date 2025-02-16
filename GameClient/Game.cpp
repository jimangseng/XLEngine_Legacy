#include "Game.h"

#include "../XLEngine/XLEngine.h"
#include "../XLEngine/Cube.h"
#include "../XLEngine/Timer.h"
#include <iostream>
using namespace XL::GamePlay;
using namespace XL::Math;
using namespace XL::GameObjects;

void Game::Start()
{
	//std::vector<Cube> cubes;

	Cube cube1;
	cube1.size = 0.8f;
	cube1.Translate(0.0f, 0.0f, 4.0f);
	scene.AddObject(cube1);

	Cube cube2;
	cube2.size = 0.4f;
	cube2.Translate(0.0f, 0.0f, 10.0f);
	scene.AddObject(cube2);

	//Cube cube4;
	//cube4.size = 0.1f;
	//cube4.color = XL::Math::Vector4( 0.5f, 0.5f, 0.2f, 1.0f );	// 노랑
	//cube4.Translate(0.1f, 0.0f, 0.0f);
	////cube4.Yaw(30.0f);	// todo: Transform 구현
	////cube4.Rotate(0.0f, 30.0f, 0.0f);
	//scene.AddObject(cube4);



}

void Game::Update()
{
	std::cout << Timer::deltaTime << std::endl;
	std::cout << Timer::frateRate << std::endl;
	std::cout << Timer::time << std::endl << std::endl;

	// todo: scene 안으로 접근하지 않도록 수정
	//scene.GetObject(0)->SetPosition(0.05f * sin(Timer::time * Timer::deltaTime), 0.0f, 0.0f);
	//scene.GetObject(0)->Translate()
	scene.GetObject(0)->Rotate(0.0f, 0.5f * Timer::deltaTime, 0.0f);
	scene.GetObject(1)->Rotate(1.5f * Timer::deltaTime, 0.0f, 1.5f * Timer::deltaTime);
}

void Game::Finish()
{
}
