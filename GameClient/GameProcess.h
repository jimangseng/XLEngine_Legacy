#pragma once

#include <windows.h>
#include <memory>
#include "../XLEngine/Engine.h"
#include "Game.h"

class GameProcess
{
public:
	GameProcess(HWND _hWnd);

public:
	void Start();
	void Update();
	void Finish();

private:
	std::unique_ptr<XL::XLEngine> engine;
	std::unique_ptr<Game> game;
};