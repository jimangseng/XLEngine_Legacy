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

// �� �̰͸� Graphics���� ���������� ȣ������
// todo: ������ Ŭ������ ������ �����ΰ�? �Һи��ϴ�
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
		// dynamic cast�� ������ ����
		// gameObject�� IObject Ÿ��ó�� ��������, ��� �̰��� ���������� ���̴�.
		// �������� IObject�� IRenderable�� ���߻�ӹ��� Cube�̸�, �������� ���� ��ĳ���� �� ���̴�.
		// ������ IRenderable�� �ٿ�ĳ���� �� �� �ִ� ���̴�
		// ���: �������� Cube�̰� ���߻���� �ޱ� �����̴�

		// GameScene���� Addobject()�� �� �� ��ĳ��Ʈ�� �߻��Ǿ���
		v.emplace_back(dynamic_pointer_cast<Components::IRenderable>(gameObject));
	}

	return v;
}
