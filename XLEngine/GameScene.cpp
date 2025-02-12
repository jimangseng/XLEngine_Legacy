#include "GameScene.h"

void XL::GamePlay::GameScene::Start()
{
	for (auto& object : objects)
	{
		object->InitializeGameObject();
	}
}

void XL::GamePlay::GameScene::Update()
{
	for (auto& object : objects)
	{
		object->UpdateGameObject();
	}
}

void XL::GamePlay::GameScene::Finish()
{
	for (auto& object : objects)
	{
		object->FinalizeGameObject();
	}
}
