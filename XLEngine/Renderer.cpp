#include "Renderer.h"
#include <vector>

#include "Cube.h"

void XL::Graphics::D3D11::Renderer::Initialize()
{
	deviceContext = resources.deviceContext.get();

	BindResources();
}

void XL::Graphics::D3D11::Renderer::Update()
{
	BindView();

	currentScene->Draw();

	UnbindView();
}

void XL::Graphics::D3D11::Renderer::Finalize()
{
	// Todo: UnbindResources();

	currentScene->Finalize();
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void XL::Graphics::D3D11::Renderer::BindResources()
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->RSSetState(resources.rasterizerState.get());

	deviceContext->OMSetDepthStencilState(resources.depthStencilState.get(), 0);
	deviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);

	D3D11_VIEWPORT viewport = { 0, 0, (float)resources.ScreenWidth, (float)resources.ScreenHeight, 0, 1 };
	deviceContext->RSSetViewports(1, &viewport);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


void XL::Graphics::D3D11::Renderer::BindView()
{
	// binding RTV to pipline OM Stage
	deviceContext->OMSetRenderTargets(1, resources.RenderTargetViews.data(), NULL);

	deviceContext->ClearRenderTargetView(resources.renderTargetView.get(), backgroundColor);
	//deviceContext->ClearDepthStencilView(depthStencilView.get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void XL::Graphics::D3D11::Renderer::UnbindView()
{
	// present swap chain
	resources.swapChain->Present1(0, 0, &presentParams);
}

void XL::Graphics::D3D11::Renderer::SetCurrentScene(XL::Graphics::RenderScene* _scene)
{
    currentScene = _scene;
}
