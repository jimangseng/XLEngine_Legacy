#include <vector>
#include "GraphicsEngine.h"
#include "GameScene.h"

// todo: 
void XL::Graphics::GraphicsEngine::Initialize(GamePlay::GameScene* _gameScene)
{
	// ���� �� �ʱ�ȭ
	// ������ �ʱ�ȭ
	// �������� �� ����

	renderScene->Initialize(_gameScene);

	renderer->Initialize();
	renderer->SetCurrentScene(renderScene.get());

}

void XL::Graphics::GraphicsEngine::Update(GamePlay::GameScene* _gameScene)
{
	renderScene->Update(_gameScene);

	renderer->Draw();
}

void XL::Graphics::GraphicsEngine::Finalize()
{
	renderScene->Finalize();
	renderer->Finalize();
}