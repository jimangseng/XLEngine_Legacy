#pragma once

#include "common.h"
#include <winrt\base.h>

using namespace DirectX;
using namespace winrt;
class XLD3DInstance
{
public:
	XLD3DInstance(HWND _hWnd)
		:
		m_hWnd(_hWnd)
	{

	}

public:
	void D3DInitialize();
	void D3DUpdate();

private:
	void BuildCOMs();
	void BindCOMsToPipeline();

private:
	/// DX관련 ///
	// Factory
	com_ptr<IDXGIFactory2> factory;

	// Adapter
	com_ptr<IDXGIAdapter1> adapter;

	// Swap Chain
	com_ptr<IDXGISwapChain1> swapChain;

	// Device
	com_ptr<ID3D11Device> device;

	// Device context
	com_ptr<ID3D11DeviceContext> deviceContext;

	/// Render Target
	// RenderTarget
	com_ptr<ID3D11Texture2D> renderTarget;

	// RenderTargetView
	com_ptr<ID3D11RenderTargetView> renderTargetView;
	ID3D11RenderTargetView* RTVs[2];

	/// Depth Stencil
	// Depth Stencil Buffer
	com_ptr<ID3D11Texture2D> depthStencilBuffer;

	// Depth Stencil View
	com_ptr<ID3D11DepthStencilView> depthStencilView;

	// Depth Stencil State
	com_ptr<ID3D11DepthStencilState> depthStencilState;

	// Swapchain Present Parameters
	DXGI_PRESENT_PARAMETERS presentParams{ 0, NULL, NULL, NULL };

	/// Buffer, InputLayout
	// Vertex Buffer
	com_ptr<ID3D11Buffer> vertexBuffer;
	ID3D11Buffer* VBs[1];
	
	// Index Buffer
	com_ptr<ID3D11Buffer> indexBuffer;

	// Input Layout
	com_ptr<ID3D11InputLayout> inputLayout;

	/// Shader
	// Compiled Shader ByteCode
	com_ptr<ID3DBlob> vertexShaderByteCode;
	com_ptr<ID3DBlob> pixelShaderByteCode;

	// Shader Resource View
	com_ptr<ID3D11ShaderResourceView> shaderResourceView;

	// Vertex Shader
	com_ptr<ID3D11VertexShader> vertexShader;

	// Pixel Shader
	com_ptr<ID3D11PixelShader> pixelShader;

	/// Rasterizer
	// Rasterizer State
	com_ptr<ID3D11RasterizerState> rasterizerState;
	
	com_ptr<ID3D11BlendState> blendState;

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};


	/// 기타
	// HRESULT
	HRESULT result;

	// Window Handle
	HWND m_hWnd;

	int ScreenWidth;
	int ScreenHeight;

	// Background Color
	float backgroundColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

};