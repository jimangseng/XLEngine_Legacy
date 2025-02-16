#include <vector>

#include "RenderScene.h"
#include "GameScene.h"

void XL::Graphics::RenderScene::Initialize(GamePlay::GameScene* _gameScene)
{
	renderObjects = Load(_gameScene);

	for (auto& object : renderObjects)
	{
		object->GetMesh()->Initialize();
	}
}

void XL::Graphics::RenderScene::Update(GamePlay::GameScene* _gameScene)
{
	renderObjects.clear();
	renderObjects = Load(_gameScene);

	for (auto& object : renderObjects)
	{
		object->GetMesh()->Update();
	}
}

// 왜 이것만 Graphics에서 렌더러에서 호출하지
// todo: 렌더러 클래스의 역할은 무엇인가? 불분명하다
void XL::Graphics::RenderScene::Draw()
{
	for (auto& object : renderObjects)
	{
		object->GetMesh()->Draw();
	}
}

void XL::Graphics::RenderScene::Finalize()
{
	for (auto& object : renderObjects)
	{
		object->GetMesh()->Finalize();
	}

	delete[] renderObjects.data();
}

std::vector<std::shared_ptr<XL::Components::IRenderable>> XL::Graphics::RenderScene::Load(GamePlay::GameScene* _gameScene)
{
	std::vector<std::shared_ptr<Components::IRenderable>> v;

	for (auto& gameObject : _gameScene->GetObjects())
	{
		// dynamic cast가 성공한 이유
		// gameObject는 IObject 타입처럼 보이지만, 사실 이것은 참조형식일 뿐이다.
		// 실형식은 IObject와 IRenderable을 다중상속받은 Cube이며, 다형성을 위해 업캐스팅 된 것이다.
		// 때문에 IRenderable로 다운캐스팅 될 수 있는 것이다
		// 요약: 실형식이 Cube이고 다중상속을 받기 때문이다

		// GameScene에서 Addobject()를 할 때 업캐스트가 발생되었다
		v.emplace_back(dynamic_pointer_cast<Components::IRenderable>(gameObject));
	}

	return v;
}
