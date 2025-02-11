#include "Engine.h"
#include <memory>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

void XL::XLEngine::Initialize(GamePlay::GameScene* _gameScene)
{
	gamePlayEngine.SetScene(_gameScene);

	gamePlayEngine.Initialize();
	graphicsEngine.Initialize();

	graphicsEngine.SyncScene(gamePlayEngine.GetScene());
}

void XL::XLEngine::Update()
{
	gamePlayEngine.Update();
	graphicsEngine.SyncScene(gamePlayEngine.GetScene());
	graphicsEngine.Update();
}

void XL::XLEngine::Finalize()
{
	gamePlayEngine.Finalize();
	graphicsEngine.Finalize();
}