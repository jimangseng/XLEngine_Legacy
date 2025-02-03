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

		// ÀÚ¿øµé
		public:
			static com_ptr<ID3D11Device> device;
			static com_ptr<ID3D11DeviceContext> deviceContext;


			static com_ptr<IDXGIFactory2> factory;
			static com_ptr<IDXGIAdapter1> adapter;

			static com_ptr<IDXGISwapChain1> swapChain;

			static com_ptr<ID3D11Texture2D> renderTarget;
			static com_ptr<ID3D11RenderTargetView> renderTargetView;
			static std::vector<ID3D11RenderTargetView*> RTVs;	// render target views

			static com_ptr<ID3D11Texture2D> depthStencilBuffer;
			static com_ptr<ID3D11DepthStencilView> depthStencilView;

			static com_ptr<ID3D11DepthStencilState> depthStencilState;

			static DXGI_PRESENT_PARAMETERS presentParams;	// swap chain present parameters

			static com_ptr<ID3D11ShaderResourceView> shaderResourceView;


			static com_ptr<ID3D11RasterizerState> rasterizerState;

			static com_ptr<ID3D11BlendState> blendState;

			// misc
			static int ScreenWidth;
			static int ScreenHeight;

			static HWND hWnd;	// window handle

			//static const float backgroundColor[4];
		};
	}
}