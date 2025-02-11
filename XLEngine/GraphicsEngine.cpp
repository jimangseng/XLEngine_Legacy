#include "GraphicsEngine.h"
#include <vector>

void XL::GraphicsEngine::Initialize()
{
	// Todo: ResourceManager ������Ű��
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
		// dynamic cast�� ������ ����
		// gameObject�� IObject Ÿ��ó�� ��������, ��� �̰��� ���������� ���̴�.
		// �������� IObject�� IRenderable�� ���߻�ӹ��� Cube�̸�, �������� ���� ��ĳ���� �� ���̴�.
		// ������ IRenderable�� �ٿ�ĳ���� �� �� �ִ� ���̴�
		// ���: �������� Cube�̰� ���߻���� �ޱ� �����̴�
		scene->renderObjects.emplace_back(dynamic_pointer_cast<IRenderable>(gameObject));
	}

	scene->Initialize();
	scene->Build();
}
