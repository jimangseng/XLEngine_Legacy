#include "RenderScene.h"

void XL::Graphics::RenderScene::Build()
{
	for (auto& object : objects)
	{
		object->Build();
	}
}

void XL::Graphics::RenderScene::Draw()
{
	for (auto& object : objects)
	{
		object->Draw();
	}
}

void XL::Graphics::RenderScene::Finalize()
{
	delete[] objects.data();
	delete[] gameObjects.data();
}

void XL::Graphics::RenderScene::SetGameObjects(std::vector<std::shared_ptr<IObject>> _gameObjects)
{
	gameObjects = _gameObjects;
}

void XL::Graphics::RenderScene::Sync(XL::GamePlay::GameScene* _gameScene)
{
	SetGameObjects(_gameScene->objects);

	for (auto& gameObject : gameObjects)
	{
		// 어떻게 IObject에서 IRenderable로 변환할 것인가?
		// dynamic_pointer_cast가 어떻게 작동하는가?
		objects.emplace_back(dynamic_pointer_cast<IRenderable>(gameObject));
	}

}
