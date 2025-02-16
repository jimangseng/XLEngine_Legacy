#include "Engine.h"
#include <memory>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

void XL::XLEngine::Initialize()
{
	gamePlayEngine.SetScene(currentScene);
	gamePlayEngine.Initialize();

	graphicsEngine.Initialize(gamePlayEngine.GetScene());
}

void XL::XLEngine::Update()
{
	gamePlayEngine.Update();
	graphicsEngine.Update(gamePlayEngine.GetScene());
}

void XL::XLEngine::Finalize()
{
	gamePlayEngine.Finalize();
	graphicsEngine.Finalize();
}