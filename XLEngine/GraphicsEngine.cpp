#include "GraphicsEngine.h"
#include "Builder.h"
#include <vector>

void XL::GraphicsEngine::Initialize()
{
	BuildResources(); // todo: getInstance(?)

	renderer->Initialize();

	scene->Build();
	renderer->SetCurrentScene(scene.get());

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