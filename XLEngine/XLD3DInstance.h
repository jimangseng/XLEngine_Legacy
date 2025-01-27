#pragma once
#include "common.h"

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
	// HRESULT
	HRESULT result;

	// Window Handle
	HWND m_hWnd;

	// Background Color
	float backgroundColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

};