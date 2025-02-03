#include "Engine.h"
#include "Builder.h"
#include <memory>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

void XL::XLEngine::Initialize()
{
	scene = CreateScene();
	scene->Initialize();

	gamePlayEngine->Initialize();
	graphicsEngine->Initialize();

	scene->Build(); // todo
	graphicsEngine->renderer->SetCurrentScene(scene);
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

void XL::GamePlayEngine::Initialize()
{

}

void XL::GamePlayEngine::Update()
{

}

void XL::GamePlayEngine::Finalize()
{

}

void XL::GraphicsEngine::Initialize()
{
	BuildResources(); // todo: a

	renderer->Initialize();

}

void XL::GraphicsEngine::Update()
{
	renderer->Update();
}

void XL::GraphicsEngine::Finalize()
{
	renderer->Finalize();
}

void XL::GraphicsEngine::BuildResources()
{
	unique_ptr<XL::D3D11::Builder> builder = make_unique<XL::D3D11::Builder>();

	builder->BuildDeviceAndSwapChain();
	builder->SetRasterizerState();
	builder->BuildRenderTargetView();
	builder->BuildDepthStencilView();
	builder->SetDepthStencilState();
	builder->SetBlendState();
}

Scene* XL::XLEngine::CreateScene()
{
	// Todo: 그래픽스 엔진이 아닌, Gameplay 엔진 쪽으로 들어가야 할 코드이다
	Scene* scene = new Scene();

	shared_ptr<Cube> cube;

	cube = make_shared<Cube>();
	cube->size = 0.8f;
	cube->color = XMFLOAT4{ 0.0f, 0.5f, 1.0f, 1.0f };	// 하늘
	scene->objects.emplace_back(cube);

	cube = make_shared<Cube>();
	cube->size = 0.5f;
	cube->color = XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f };	// 빨강
	scene->objects.emplace_back(cube);

	cube = make_shared<Cube>();
	cube->size = 0.3f;
	cube->color = XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f };	// 파랑
	scene->objects.emplace_back(cube);

	cube = make_shared<Cube>();
	cube->size = 0.1f;
	cube->color = XMFLOAT4{ 1.0f, 1.0f, 0.0f, 1.0f };	// 노랑
	cube->Translate({ 1.0f, 0.0f, 0.0f });
	scene->objects.emplace_back(cube);

	return scene;
}
