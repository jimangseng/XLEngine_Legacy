#include "GameProcess.h"
#include "Game.h"

#pragma comment (lib, "XLEngine.lib")

GameProcess::GameProcess(HWND _hWnd)
	:engine(XL::XLEngine(_hWnd)),
	gameInstance(std::make_unique<Game>())
{

}

void GameProcess::Start()
{
	gameInstance->Start();
	engine.Initialize(gameInstance->GetScene());
}

void GameProcess::Update()
{
	gameInstance->Update();
	engine.Update();
}

void GameProcess::Finish()
{
	engine.Finalize();
}