#include "Renderer.h"
#include <vector>

#include "Cube.h"

void XL::D3D11::Renderer::Initialize()
{
	deviceContext = Resources::deviceContext.get();

	BindResources();
}

void XL::D3D11::Renderer::Update()
{
	BindView();

	currentScene->Draw();

	UnbindView();
}

void XL::D3D11::Renderer::Finalize()
{
	currentScene->Finalize();
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void XL::D3D11::Renderer::BindResources()
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->RSSetState(XL::D3D11::Resources::rasterizerState.get());

	deviceContext->OMSetDepthStencilState(XL::D3D11::Resources::depthStencilState.get(), 0);
	deviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);

	D3D11_VIEWPORT viewport = { 0, 0,XL::D3D11::Resources::ScreenWidth, XL::D3D11::Resources::ScreenHeight, 0, 1 };
	deviceContext->RSSetViewports(1, &viewport);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


void XL::D3D11::Renderer::BindView()
{
	// binding RTV to pipline OM Stage
	deviceContext->OMSetRenderTargets(1, XL::D3D11::Resources::RTVs.data(), NULL);

	deviceContext->ClearRenderTargetView(XL::D3D11::Resources::renderTargetView.get(), new float[4]{0.1f, 0.1f, 0.1f, 1.0f});
	//deviceContext->ClearDepthStencilView(depthStencilView.get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void XL::D3D11::Renderer::UnbindView()
{
	// present swap chain
	XL::D3D11::Resources::swapChain->Present1(0, 0, &XL::D3D11::Resources::presentParams);
	//XL::D3D11::Resources::swapChain->Present1(0, 0, nullptr);
}

void XL::D3D11::Renderer::SetCurrentScene(Scene* _scene)
{
	currentScene = _scene;
}
