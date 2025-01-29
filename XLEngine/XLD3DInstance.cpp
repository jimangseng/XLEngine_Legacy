#include "XLD3DInstance.h"
#include <vector>

void XLD3DInstance::D3DInitialize()
{
	BuildCOMs();
	BindCOMsToPipeline();
}

void XLD3DInstance::D3DUpdate()
{
	// binding RTV to pipline OM Stage
	//deviceContext->OMSetRenderTargets(1, RTVs, depthStencilView.get());
	deviceContext->OMSetRenderTargets(1, RTVs, NULL);

	// clear DSV
	//deviceContext->ClearDepthStencilView(depthStencilView.get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	// clear RTV
	deviceContext->ClearRenderTargetView(renderTargetView.get(), backgroundColor);

	// Draw Call
	deviceContext->DrawIndexed(3, 0, 0);

	// present swap chain
	swapChain->Present1(0, 0, &presentParams);

}

void XLD3DInstance::BuildCOMs()
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
		device.put(),
		nullptr,
		deviceContext.put()
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
		DXGI_SCALING_NONE,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_IGNORE,
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

	RTVs[0] = renderTargetView.get();


	// Create Vertex Buffer

	Vertex vertices[3] =
	{
		Vertex{ {0.0f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
		Vertex{ {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
		Vertex{ {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} }
	};

	D3D11_BUFFER_DESC vbDesc
	{
		sizeof(Vertex) * 3,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		NULL,
		NULL,
		sizeof(Vertex)
	};

	D3D11_SUBRESOURCE_DATA vbData
	{
		vertices,
		0,
		0
	};

	result = device->CreateBuffer(&vbDesc, &vbData, vertexBuffer.put());


	// Create Index Buffer
	int indices[3]{ 0, 1, 2 };

	D3D11_BUFFER_DESC ibDesc
	{
		sizeof(indices),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_INDEX_BUFFER,
		NULL,
		NULL,
		sizeof(int)
	};

	D3D11_SUBRESOURCE_DATA ibData
	{
		indices,
		0,
		0
	};

	result = device->CreateBuffer(&ibDesc, &ibData, indexBuffer.put());

	// Loading Shader ByteCode
	result = D3DReadFileToBlob(TEXT("../Shader/VertexShader.cso"), vertexShaderByteCode.put());
	result = D3DReadFileToBlob(TEXT("../Shader/PixelShader.cso"), pixelShaderByteCode.put());

	// Create Input Layout
	D3D11_INPUT_ELEMENT_DESC intputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	result = device->CreateInputLayout
	(
		intputElementDesc,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		inputLayout.put()
	);

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



	// Create Rasterizer State
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




	// create DSB
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

	// create depth stencil state
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

	//create blend state

	D3D11_BLEND_DESC blendDesc =
	{
		false, false, NULL
	};

	device->CreateBlendState(&blendDesc, blendState.put());
}

void XLD3DInstance::BindCOMsToPipeline()
{
	// binding InputLayout to pipline IA Stage 
	deviceContext->IASetInputLayout(inputLayout.get());

	// binding Buffers to pipeline IA Stage
	VBs[0] = vertexBuffer.get();
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	deviceContext->IASetVertexBuffers(0, 1, VBs, &strides, &offsets);
	deviceContext->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

	// Set Primitive Topology
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// binding shaders to pipline
	deviceContext->VSSetShader(vertexShader.get(), NULL, NULL);
	deviceContext->PSSetShader(pixelShader.get(), NULL, NULL);

	// binding DSS to pipeline OM Stage
	deviceContext->OMSetDepthStencilState(depthStencilState.get(), 0);

	//deviceContext->OMSetBlendState(blendState.get(), NULL, NULL);
	deviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);

	// Set viewport
	D3D11_VIEWPORT viewport = { 0, 0, ScreenWidth, ScreenHeight, 0, 1 };
	deviceContext->RSSetViewports(1, &viewport);
}
