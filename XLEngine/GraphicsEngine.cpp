#include "GraphicsEngine.h"
#include <vector>

void XL::GraphicsEngine::Initialize()
{
	// Todo: ResourceManager 발전시키기
	XL::D3D11::Resources& resources = XL::D3D11::Resources::GetInstance();
	resources.Build();

	//scene->Initialize();

	renderer->Initialize();
	renderer->SetCurrentScene(scene.get());

}

void XL::GraphicsEngine::Update()
{
	scene->RenderUpdate();

	renderer->Update();
}

void XL::GraphicsEngine::Finalize()
{
	renderer->Finalize();
}
void XL::GraphicsEngine::SyncScene(XL::GamePlay::GameScene* _gameScene)
{
	scene->renderObjects.clear();

	for (auto& gameObject : _gameScene->objects)
	{
		// TODO:
		// 어떻게 IObject에서 IRenderable로 변환할 것인가?
		// pointer_cast가 어떻게 작동하는가?
		// 왜 dynamic은 되고 static은 안되는가?
		scene->renderObjects.emplace_back(dynamic_pointer_cast<IRenderable>(gameObject));
	}

	scene->Initialize();
	scene->Build();
}
