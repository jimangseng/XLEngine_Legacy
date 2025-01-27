#include "XLEngine.h"


#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

XLEngine::XLEngine(HWND _hWnd)
{
	m_hWnd = _hWnd;
}

void XLEngine::Initialize()
{
	// create factory
	result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), factory.put_void());

	// enumerate adapter
	result = factory->EnumAdapters1(0, adapter.put());

	//create device
	result = D3D11CreateDevice
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		device.put(),
		nullptr,
		deviceContext.put()
	);

	// swap chain description
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc =
	{
		0,
		0,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		false,
		{1, 0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_NONE,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_UNSPECIFIED,
		0
	};

	// create swap chain
	result = factory->CreateSwapChainForHwnd
	(
		device.get(),
		m_hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		swapChain.put()
	);

	// get render target from swap chain
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), renderTarget.put_void());

	// create RTV
	result = device->CreateRenderTargetView
	(
		renderTarget.get(),
		NULL,
		renderTargetView.put()
	);

	RTVs[0] = renderTargetView.get();

	// binding RTV to pipline OM Stage
	deviceContext->OMSetRenderTargets
	(
		1,
		RTVs,
		NULL
	);
}

void XLEngine::Update()
{
	// clear RTV
	deviceContext->ClearRenderTargetView(renderTargetView.get(), backgroundColor);

	// present swap chain
	swapChain->Present1(0, 0, &presentParams);
}

void XLEngine::Finalize()
{

}
