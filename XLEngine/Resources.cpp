#include "Resources.h"

void XL::Graphics::D3D11::Resources::Build()
{
	BuildDeviceAndSwapChain();
	SetRasterizerState();
	BuildRenderTargetView();
	BuildDepthStencilView();
	SetDepthStencilState();
	SetBlendState();
	SetSamplerState();
}

void XL::Graphics::D3D11::Resources::BuildDeviceAndSwapChain()
{
	using namespace XL::Graphics::D3D11;

	// create factory
	result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), Resources::factory.put_void());

	// enumerate adapter
	result = Resources::factory->EnumAdapters1(0, Resources::adapter.put());

	// create device
	result = D3D11CreateDevice
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		Resources::device.put(),
		nullptr,
		Resources::deviceContext.put()
	);

	// swap chain description
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc =
	{
		0,
		0,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		false,
		{1, 0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_IGNORE,
		0
	};

	// create swap chain
	result = Resources::factory->CreateSwapChainForHwnd
	(
		Resources::device.get(),
		Resources::hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		Resources::swapChain.put()
	);
}

void XL::Graphics::D3D11::Resources::SetRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc =
	{
		D3D11_FILL_SOLID,
		D3D11_CULL_BACK,
		false,
		0,
		0.0f,
		0.0f,
		false,
		false,
		false,
		false
	};

	result = Resources::device.get()->CreateRasterizerState(&rasterizerDesc, Resources::rasterizerState.put());

}

void XL::Graphics::D3D11::Resources::BuildRenderTargetView()
{
	// get render target from swap chain
	result = Resources::swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), Resources::renderTarget.put_void());

	D3D11_TEXTURE2D_DESC tDesc;
	Resources::renderTarget->GetDesc(&tDesc);
	Resources::ScreenWidth = tDesc.Width;
	Resources::ScreenHeight = tDesc.Height;

	// create RTV
	result = Resources::device->CreateRenderTargetView
	(
		Resources::renderTarget.get(),
		NULL,
		Resources::renderTargetView.put()
	);

	Resources::RenderTargetViews.emplace_back(Resources::renderTargetView.get());
}

void XL::Graphics::D3D11::Resources::BuildDepthStencilView()
{
	D3D11_TEXTURE2D_DESC dsbDesc =
	{
		(UINT)Resources::ScreenWidth,
		(UINT)Resources::ScreenHeight,
		0,
		1,
		DXGI_FORMAT_D16_UNORM,
		{1, 0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL,
		NULL,
		NULL
	};
	result = Resources::device.get()->CreateTexture2D
	(
		&dsbDesc,
		NULL,
		Resources::depthStencilBuffer.put()
	);
	const D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc =
	{
		DXGI_FORMAT_D16_UNORM,
		D3D11_DSV_DIMENSION_TEXTURE2D,
		0
	};
	result = Resources::device.get()->CreateDepthStencilView
	(
		Resources::depthStencilBuffer.get(),
		&dsvDesc,
		Resources::depthStencilView.put()
	);
}

void XL::Graphics::D3D11::Resources::SetDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc =
	{
		false,
		D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_COMPARISON_LESS,
		false,
		D3D11_DEFAULT_STENCIL_READ_MASK,
		D3D11_DEFAULT_STENCIL_WRITE_MASK,
		{ D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS },
		{ D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS },
	};

	result = Resources::device->CreateDepthStencilState
	(&depthStencilDesc, Resources::depthStencilState.put());
}

void XL::Graphics::D3D11::Resources::SetBlendState()
{
	//create blend state
	D3D11_BLEND_DESC blendDesc =
	{
		false, false, NULL
	};

	Resources::device->CreateBlendState(&blendDesc, Resources::blendState.put());
}

void XL::Graphics::D3D11::Resources::SetSamplerState()
{
	D3D11_SAMPLER_DESC desc{};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	result = device->CreateSamplerState(&desc, samplerState.put());
}
