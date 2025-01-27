#pragma once

#include "dxgi1_2.h"
#include "d3d11.h"

#include <winrt\base.h>

using namespace std;
using namespace winrt;
class XLEngine
{
public:

	XLEngine(HWND _hWnd);

	void Initialize();
	void Update();
	void Finalize();

private:
	/// DX관련
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

	// RenderTarget
	com_ptr<ID3D11Texture2D> renderTarget;

	// RenderTargetView
	com_ptr<ID3D11RenderTargetView> renderTargetView;
	ID3D11RenderTargetView* RTVs[1];

	// Swapchain Present Parameters
	DXGI_PRESENT_PARAMETERS presentParams{ 0, NULL, NULL, NULL };


	/// 기타
	// Window Handle
	HWND m_hWnd;

	// HRESULT
	HRESULT result;

	// Background Color
	float backgroundColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
};

