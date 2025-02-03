#include "Resources.h"

com_ptr<ID3D11Device> XL::D3D11::Resources::device;
com_ptr<ID3D11DeviceContext> XL::D3D11::Resources::deviceContext;

com_ptr<IDXGIFactory2> XL::D3D11::Resources::factory;
com_ptr<IDXGIAdapter1> XL::D3D11::Resources::adapter;

com_ptr<IDXGISwapChain1> XL::D3D11::Resources::swapChain;

com_ptr<ID3D11Texture2D> XL::D3D11::Resources::renderTarget;
com_ptr<ID3D11RenderTargetView> XL::D3D11::Resources::renderTargetView;
std::vector<ID3D11RenderTargetView*> XL::D3D11::Resources::RTVs;	// render target views

com_ptr<ID3D11Texture2D> XL::D3D11::Resources::depthStencilBuffer;
com_ptr<ID3D11DepthStencilView> XL::D3D11::Resources::depthStencilView;

com_ptr<ID3D11DepthStencilState> XL::D3D11::Resources::depthStencilState;

DXGI_PRESENT_PARAMETERS XL::D3D11::Resources::presentParams;	// swap chain present parameters

com_ptr<ID3D11ShaderResourceView> XL::D3D11::Resources::shaderResourceView;


com_ptr<ID3D11RasterizerState> XL::D3D11::Resources::rasterizerState;

com_ptr<ID3D11BlendState> XL::D3D11::Resources::blendState;

 int XL::D3D11::Resources::ScreenWidth;
 int XL::D3D11::Resources::ScreenHeight;

 HWND XL::D3D11::Resources::hWnd;	// window handle

 //float XL::D3D11::Resources::backgroundColor[4];