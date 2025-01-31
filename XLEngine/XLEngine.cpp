#include "XLEngine.h"
#include <memory>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

XLEngine::XLEngine(HWND _hWnd)
	:
	renderer(std::make_unique<XLD3DRenderer>(_hWnd))
{

}

void XLEngine::Initialize()
{
	renderer->D3DInitialize();
}

void XLEngine::Update()
{
	renderer->D3DUpdate();
}

void XLEngine::Finish()
{
	renderer->D3DFinalize();
}