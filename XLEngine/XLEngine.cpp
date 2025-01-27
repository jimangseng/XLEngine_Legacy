#include "XLEngine.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

XLEngine::XLEngine(HWND _hWnd)
	:instance(new XLD3DInstance(_hWnd))
{

}

void XLEngine::Initialize()
{
	instance->D3DInitialize();
}

void XLEngine::Update()
{
	instance->D3DUpdate();
}

void XLEngine::Finish()
{

}