#pragma once

#include "common.h"
#include <vector>
#include "XLD3DResources.h"
#include "Scene.h"

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

private:
	void LoadScene();
	void BuildCOM();
	void BuildGeometries();
	void BindCOM();

private:
	void BuildDeviceAndSwapChain();
	void SetRasterizerState();
	void BuildRenderTargetView();
	void BuildDepthStencilView();
	void SetDepthStencilState();
	void SetBlendState();

private:
	void BindView();
	void UnbindView();


private:
	com_ptr<IDXGIFactory2> factory;
	com_ptr<IDXGIAdapter1> adapter;

	// "XLD3DResource" 에서 com_ptr로 관리하며, 생 포인터를 받아와 사용한다
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	com_ptr<IDXGISwapChain1> swapChain;

private:
	com_ptr<ID3D11Texture2D> renderTarget;
	com_ptr<ID3D11RenderTargetView> renderTargetView;
	std::vector<ID3D11RenderTargetView*> RTVs;	// render target views

	com_ptr<ID3D11Texture2D> depthStencilBuffer;
	com_ptr<ID3D11DepthStencilView> depthStencilView;

	com_ptr<ID3D11DepthStencilState> depthStencilState;

	DXGI_PRESENT_PARAMETERS presentParams{ 0, NULL, NULL, NULL };	// swap chain present parameters

	com_ptr<ID3D11ShaderResourceView> shaderResourceView;


	com_ptr<ID3D11RasterizerState> rasterizerState;

	com_ptr<ID3D11BlendState> blendState;

	// misc
	int ScreenWidth;
	int ScreenHeight;

	HWND hWnd;	// window handle
	HRESULT result;

	Scene* scene;

	float backgroundColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
};