#pragma once

#include <windows.h>
#include <memory>
#include "../XLEngine/Engine.h"

class Game
{
public:
	Game(HWND _hWnd);

public:
	void Start();
	void Update();
	void Finish();

private:
	std::unique_ptr<XL::XLEngine> engine;
};