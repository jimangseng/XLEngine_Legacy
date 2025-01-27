#pragma once

#include "XLD3DInstance.h"

using namespace std;
class XLEngine
{
public:

	XLEngine(HWND _hWnd);

	void Initialize();
	void Update();
	void Finish();

private:
	XLD3DInstance* instance;

};