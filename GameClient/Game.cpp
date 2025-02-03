#include "Game.h"

#pragma comment (lib, "XLEngine.lib")

Game::Game(HWND _hWnd)
	:engine(std::make_unique<XL::XLEngine>(_hWnd))
{
}

void Game::Start()
{
	engine->Initialize();
}

void Game::Update()
{
	engine->Update();
}

void Game::Finish()
{
	engine->Finalize();
}