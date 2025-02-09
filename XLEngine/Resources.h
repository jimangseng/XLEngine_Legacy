#pragma once

#include "Common.h"

namespace XL
{
	namespace D3D11
	{
		class Resources
		{
		public:
			Resources() = default;
			~Resources() = default;
			Resources(const Resources& ref) = delete;
			Resources& operator= (const Resources& ref) = delete;

		public:
			// ½Ì±ÛÅæ °´Ã¼ ¹ÝÈ¯
			static Resources& GetInstance()
			{
				static Resources instance;

				return instance;
			}

			//static ID3D11Device* const GetDevice()
			//{
			//	return device.get();
			//}

			//static ID3D11DeviceContext* const GetDeviceContext()
			//{
			//	return deviceContext.get();
			//}

			//static ID3D11Device** PutDevice()
			//{
			//	return device.put();
			//}

			//static ID3D11DeviceContext** PutDeviceContext()
			//{
			//	return deviceContext.put();
			//}

		public:
			void Build();

		private:
			void BuildDeviceAndSwapChain();
			void SetRasterizerState();
			void BuildRenderTargetView();
			void BuildDepthStencilView();
			void SetDepthStencilState();
			void SetBlendState();

		// ÀÚ¿øµé
		public:
			com_ptr<ID3D11Device> device;
			com_ptr<ID3D11DeviceContext> deviceContext;

			com_ptr<IDXGIFactory2> factory;
			com_ptr<IDXGIAdapter1> adapter;

			com_ptr<IDXGISwapChain1> swapChain;

			com_ptr<ID3D11Texture2D> renderTarget;
			com_ptr<ID3D11RenderTargetView> renderTargetView;
			std::vector<ID3D11RenderTargetView*> RTVs;	// render target views

			com_ptr<ID3D11Texture2D> depthStencilBuffer;
			com_ptr<ID3D11DepthStencilView> depthStencilView;

			com_ptr<ID3D11DepthStencilState> depthStencilState;

			DXGI_PRESENT_PARAMETERS presentParams;	// swap chain present parameters

			com_ptr<ID3D11ShaderResourceView> shaderResourceView;

			com_ptr<ID3D11RasterizerState> rasterizerState;

			com_ptr<ID3D11BlendState> blendState;

			// misc
			int ScreenWidth;
			int ScreenHeight;

			HWND hWnd;	// window handle

		private:

			HRESULT result;
			//const float backgroundColor[4];
		};
	}
}