#pragma once

#include "common.h"
#include <vector>
#include "XLD3DResources.h"

using namespace DirectX;
using namespace winrt;

class Cube;

class XLD3DRenderer
{
public:
	XLD3DRenderer() = delete;
	XLD3DRenderer(const XLD3DRenderer& rhs) = delete;

	XLD3DRenderer(HWND _hWnd)
		: hWnd(_hWnd), result(NULL),
		//ScreenWidth(0), ScreenHeight(0),
		device(nullptr), deviceContext(nullptr)
	{

	}

public:
	void D3DInitialize();
	void D3DUpdate();
	void D3DFinalize();

public:
	void LoadScene();

private:
	void BuildCOMs();
	void BindCOMsToPipeline();
	void BindView();
	void UnbindView();
	void BuildGeometries();
	void BindGeometries();

private:
	void BuildDeviceAndSwapChain();
	void BuildShader();
	void SetRasterizerState();
	void BuildRenderTargetView();
	void BuildDepthStencilView();
	void SetDepthStencilState();
	void SetBlendState();

private:
	/// DX관련 ///
	// Factory
	com_ptr<IDXGIFactory2> factory;

	// Adapter
	com_ptr<IDXGIAdapter1> adapter;

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	// Swap Chain
	com_ptr<IDXGISwapChain1> swapChain;

private:
	/// Render Target
	// RenderTarget
	com_ptr<ID3D11Texture2D> renderTarget;

	// RenderTargetView
	com_ptr<ID3D11RenderTargetView> renderTargetView;
	std::vector<ID3D11RenderTargetView*> RTVs;

	/// Depth Stencil
	// Depth Stencil Buffer
	com_ptr<ID3D11Texture2D> depthStencilBuffer;

	// Depth Stencil View
	com_ptr<ID3D11DepthStencilView> depthStencilView;

	// Depth Stencil State
	com_ptr<ID3D11DepthStencilState> depthStencilState;

	// Swapchain Present Parameters
	DXGI_PRESENT_PARAMETERS presentParams{ 0, NULL, NULL, NULL };

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

	/// 기타
	int ScreenWidth;
	int ScreenHeight;

	// Window Handle
	HWND hWnd;
	HRESULT result;

	std::vector<Cube*> cubes;

	float backgroundColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
};