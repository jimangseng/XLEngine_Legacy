#include "GameScene.h"

void XL::GamePlay::GameScene::Start()
{
	//
	for (auto& object : objects)
	{
		object->Start();
	}
}

void XL::GamePlay::GameScene::AddObject(std::shared_ptr<IObject> object)
{
	objects.emplace_back(object);
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
