#pragma once

#include "Common.h"

namespace XL
{
	namespace Graphics
	{
		namespace D3D11
		{
			class Resources
			{
			public:
				Resources(const Resources& ref) = delete;
				Resources& operator= (const Resources& ref) = delete;

			private:
				// 클래스 내부에서만 기본 생성자를 호출하고, 외부에서는 호출하지 못하도록 막음
				Resources() {}
				~Resources() {}

			public:
				// 싱글톤 객체 반환
				static Resources& GetInstance()
				{
					static Resources instance;
					return instance;
				}

			public:
				void Build();

			private:
				void BuildDeviceAndSwapChain();
				void SetRasterizerState();
				void BuildRenderTargetView();
				void BuildDepthStencilView();
				void SetDepthStencilState();
				void SetBlendState();

			public:
				// D3D 자원들
				com_ptr<ID3D11Device> device;
				com_ptr<ID3D11DeviceContext> deviceContext;

				com_ptr<IDXGIFactory2> factory;
				com_ptr<IDXGIAdapter1> adapter;
				com_ptr<IDXGISwapChain1> swapChain;

				com_ptr<ID3D11Texture2D> renderTarget;
				com_ptr<ID3D11RenderTargetView> renderTargetView;
				std::vector<ID3D11RenderTargetView*> RenderTargetViews;

				com_ptr<ID3D11Texture2D> depthStencilBuffer;
				com_ptr<ID3D11DepthStencilView> depthStencilView;

				com_ptr<ID3D11DepthStencilState> depthStencilState;

				com_ptr<ID3D11ShaderResourceView> shaderResourceView;

				com_ptr<ID3D11RasterizerState> rasterizerState;

				com_ptr<ID3D11BlendState> blendState;

				// misc
				int ScreenWidth;
				int ScreenHeight;
				HWND hWnd;	// window handle

			private:
				HRESULT result;
			};
		}

	}
}