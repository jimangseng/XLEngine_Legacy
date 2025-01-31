#pragma once

#include "XLD3DRenderer.h"

#include <memory>

using namespace std;
class XLEngine
{
public:

	XLEngine(HWND _hWnd);

	void Initialize();
	void Update();
	void Finish();

private:
	unique_ptr<XLD3DRenderer> renderer;

};