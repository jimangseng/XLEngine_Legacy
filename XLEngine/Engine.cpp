#include "Engine.h"
#include "Builder.h"
#include <memory>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

void XL::XLEngine::Initialize()
{
	gamePlayEngine->Initialize();

	graphicsEngine->scene->Sync(gamePlayEngine->scene);

	graphicsEngine->Initialize();
}

void XL::XLEngine::Update()
{
	gamePlayEngine->Update();
	graphicsEngine->Update();
}

void XL::XLEngine::Finalize()
{
	gamePlayEngine->Finalize();
	graphicsEngine->Finalize();
}