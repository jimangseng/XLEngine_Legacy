#include "GameProcess.h"
#include "Game.h"

#pragma comment (lib, "XLEngine.lib")

GameProcess::GameProcess(HWND _hWnd)
	:engine(XL::XLEngine(_hWnd)),
	script(std::make_unique<Game>())
{

}

void GameProcess::Start()
{
	script->Start();
	engine.SetScene(script->GetScene());
	engine.Initialize();
}

void GameProcess::Update()
{
	script->Update();
	engine.SetScene(script->GetScene());

	engine.Update();
	script->SetScene(engine.GetScene());

}

void GameProcess::Finish()
{
	script->Finish();
	engine.Finalize();
}