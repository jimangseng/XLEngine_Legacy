#include "Game.h"
#include "../XLEngine/XLEngine.h"

using namespace XL::GamePlay;

void Game::Start()
{
	//std::vector<Cube> cubes;

	Cube cube1;
	cube1.size = 0.8f;
	cube1.color = XL::Math::Vector4(0.1f, 0.3f, 0.6f, 1.0f);	// 하늘
	scene.AddObject(cube1);

	//Cube cube2;
	//cube2.size = 0.4f;
	//cube2.color = XL::Math::Vector4(0.6f, 0.1f, 0.1f, 1.0f);	// 빨강
	//scene.AddObject(cube2);

	//Cube cube3;
	//cube3.size = 0.3f;
	//cube3.color = XL::Math::Vector4( 0.1f, 0.1f, 0.6f, 1.0f );	// 파랑
	//scene.AddObject(cube3);

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
	// todo: Timer
	time += 0.02f;

	// todo: scene 안으로 접근하지 않도록 수정
	//scene.GetObject(0)->SetPosition(0.0f, sin(time), 0.0f);
	//scene.GetObject(1)->SetPosition(sin(time), 0.0f, 0.0f);
	//scene.GetObject(2)->SetPosition(cos(time), sin(time), 0.0f);
	
	scene.GetObject(0)->Rotate(time, time, 0.0f);
	//scene.GetObject(1)->Rotate(time, time, time);
	//scene.GetObject(2)->Rotate(time, 0.0f, time);
	//scene.GetObject(3)->Rotate(0.0f, time, time);
}

void Game::Finish()
{
}
