#include "GraphicsEngine.h"
#include <vector>

void XL::GraphicsEngine::Initialize()
{
	// Todo: ResourceManager 발전시키기
	XL::Graphics::D3D11::Resources& resources = XL::Graphics::D3D11::Resources::GetInstance();
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

	for (auto& gameObject : _gameScene->GetObjects())
	{
		// dynamic cast가 성공한 이유
		// gameObject는 IObject 타입처럼 보이지만, 사실 이것은 참조형식일 뿐이다.
		// 실형식은 IObject와 IRenderable을 다중상속받은 Cube이며, 다형성을 위해 업캐스팅 된 것이다.
		// 때문에 IRenderable로 다운캐스팅 될 수 있는 것이다
		// 요약: 실형식이 Cube이고 다중상속을 받기 때문이다
		scene->renderObjects.emplace_back(dynamic_pointer_cast<IRenderable>(gameObject));
	}

	scene->Initialize();
	scene->Build();
}
