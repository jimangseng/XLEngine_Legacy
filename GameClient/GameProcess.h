#pragma once

#include <windows.h>
#include <memory>
#include "../XLEngine/Engine.h"
#include "Game.h"

class GameProcess
{
public:
	GameProcess() = delete;
	~GameProcess() = default;
	GameProcess(const GameProcess& rhs) = delete;
	GameProcess& operator= (const GameProcess& rhs) = delete;

	GameProcess(HWND _hWnd);

public:
	void Start();
	void Update();
	void Finish();

private:
	XL::XLEngine engine;
	std::unique_ptr<Game> game;
};