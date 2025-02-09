#include "GameScene.h"
#include "Cube.h"

void XL::GamePlay::GameScene::Start()
{
	for (auto& object : objects)
	{
		object->Start();
	}
}

void XL::GamePlay::GameScene::Update()
{
	for (auto& object : objects)
	{
		object->Update();
	}
}

void XL::GamePlay::GameScene::Finish()
{
	for (auto& object : objects)
	{
		object->Finish();
	}
}
