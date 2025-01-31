#include "XLD3DRenderer.h"
#include <vector>

#include "Cube.h"

void XLD3DRenderer::D3DInitialize()
{
	LoadScene();
	BuildCOMs();
	BuildGeometries();
	BindCOMsToPipeline();
}

void XLD3DRenderer::D3DUpdate()
{
	BindView();

	for (auto& cube : cubes)
	{
		cube->Draw();
	}

	UnbindView();
}

void XLD3DRenderer::D3DFinalize()
{
	delete[] cubes.data();
}

void XLD3DRenderer::LoadScene()
{
	// 외부에서 씬 불러오는 것으로 가정
	Cube* tCube = new Cube();
	tCube->size = 0.5f;
	tCube->color = XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f };
	cubes.emplace_back(tCube);

	tCube = new Cube();
	tCube->size = 0.1f;
	tCube->color = XMFLOAT4{ 1.0f, 1.0f, 0.0f, 1.0f };
	cubes.emplace_back(tCube);

	tCube = new Cube();
	tCube->size = 0.3f;
	tCube->color = XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f };
	cubes.emplace_back(tCube);
}

void XLD3DRenderer::BuildCOMs()
{
	BuildDeviceAndSwapChain();

	BuildRenderTargetView();

	SetRasterizerState();

	BuildDepthStencilView();

	SetDepthStencilState();

	SetBlendState();
}

void XLD3DRenderer::BuildGeometries()
{
	BuildShader();

	for (auto& cube : cubes)
	{
		cube->Build(vertexShaderByteCode.get());
	}
}

void XLD3DRenderer::BindCOMsToPipeline()
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->VSSetShader(vertexShader.get(), NULL, NULL);
	deviceContext->PSSetShader(pixelShader.get(), NULL, NULL);

	deviceContext->OMSetDepthStencilState(depthStencilState.get(), 0);
	deviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);

	D3D11_VIEWPORT viewport = { 0, 0, ScreenWidth, ScreenHeight, 0, 1 };
	deviceContext->RSSetViewports(1, &viewport);
}

void XLD3DRenderer::BindView()
{
	// binding RTV to pipline OM Stage
	deviceContext->OMSetRenderTargets(1, RTVs.data(), NULL);

	deviceContext->ClearRenderTargetView(renderTargetView.get(), backgroundColor);
	//deviceContext->ClearDepthStencilView(depthStencilView.get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void XLD3DRenderer::UnbindView()
{
	// present swap chain
	swapChain->Present1(0, 0, &presentParams);
}

void XLD3DRenderer::BuildDeviceAndSwapChain()
{
	// create factory
	result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), factory.put_void());

	// enumerate adapter
	result = factory->EnumAdapters1(0, adapter.put());

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
		XLD3DResources::PutDevice(),
		nullptr,
		XLD3DResources::PutDeviceContext()
	);

	device = XLD3DResources::GetDevice();
	deviceContext = XLD3DResources::GetDeviceContext();

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
		DXGI_SCALING_NONE,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_IGNORE,
		0
	};

	// create swap chain
	result = factory->CreateSwapChainForHwnd
	(
		device,
		hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		swapChain.put()
	);
}

void XLD3DRenderer::BuildShader()
{
	// Loading Shader ByteCode
	result = D3DReadFileToBlob(TEXT("../Shader/VertexShader.cso"), vertexShaderByteCode.put());
	result = D3DReadFileToBlob(TEXT("../Shader/PixelShader.cso"), pixelShaderByteCode.put());

	// Create Vertex Shader
	result = device->CreateVertexShader
	(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		NULL,
		vertexShader.put()
	);

	// Create Pixel Shader
	result = device->CreatePixelShader
	(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		NULL,
		pixelShader.put()
	);
}

void XLD3DRenderer::SetRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc =
	{
		D3D11_FILL_SOLID,
		D3D11_CULL_NONE,
		true,
		0,
		0.0f,
		0.0f,
		false,
		false,
		false,
		false
	};

	result = device->CreateRasterizerState(&rasterizerDesc, rasterizerState.put());
}

void XLD3DRenderer::BuildRenderTargetView()
{
	// get render target from swap chain
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), renderTarget.put_void());

	D3D11_TEXTURE2D_DESC tDesc;
	renderTarget->GetDesc(&tDesc);
	ScreenWidth = tDesc.Width;
	ScreenHeight = tDesc.Height;

	// create RTV
	result = device->CreateRenderTargetView
	(
		renderTarget.get(),
		NULL,
		renderTargetView.put()
	);

	RTVs.emplace_back(renderTargetView.get());
}

void XLD3DRenderer::BuildDepthStencilView()
{
	D3D11_TEXTURE2D_DESC dsbDesc =
	{
		ScreenWidth,
		ScreenHeight,
		0,
		1,
		DXGI_FORMAT_D16_UNORM,
		{1, 0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL,
		NULL,
		NULL
	};
	result = device->CreateTexture2D
	(
		&dsbDesc,
		NULL,
		depthStencilBuffer.put()
	);
	const D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc =
	{
		DXGI_FORMAT_D16_UNORM,
		D3D11_DSV_DIMENSION_TEXTURE2D,
		0
	};
	result = device->CreateDepthStencilView
	(
		depthStencilBuffer.get(),
		&dsvDesc,
		depthStencilView.put()
	);
}

void XLD3DRenderer::SetDepthStencilState()
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

	result = device->CreateDepthStencilState
	(&depthStencilDesc, depthStencilState.put());
}

void XLD3DRenderer::SetBlendState()
{
	//create blend state
	D3D11_BLEND_DESC blendDesc =
	{
		false, false, NULL
	};

	device->CreateBlendState(&blendDesc, blendState.put());
}
