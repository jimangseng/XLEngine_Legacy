#include "GameProcess.h"
#include "Game.h"

#pragma comment (lib, "XLEngine.lib")

GameProcess::GameProcess(HWND _hWnd)
	:engine(std::make_unique<XL::XLEngine>(_hWnd)),
	game(std::make_unique<Game>())
{
}

void GameProcess::Start()
{
	game->Start();
	engine->Initialize(game->GetScene());
}

void GameProcess::Update()
{
	game->Update();
	engine->Update();
}

void GameProcess::Finish()
{
	engine->Finalize();
}