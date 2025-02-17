#include "GamePlayEngine.h"
#include "GameScene.h"
#include "Timer.h"

XL::GamePlay::Timer XL::GamePlay::GamePlayEngine::timer;
XL::Camera XL::GamePlay::GamePlayEngine::mainCamera;
XL::GamePlay::InputManager XL::GamePlay::GamePlayEngine::inputManager;

void XL::GamePlay::GamePlayEngine::Initialize()
{
	timer.Initialize();
	mainCamera = gameScene->camera;
	gameScene->Start();
}

void XL::GamePlay::GamePlayEngine::Update()
{
	timer.Update();
	inputManager.Update();
	mainCamera.Update();
	gameScene->Update();
}

void XL::GamePlay::GamePlayEngine::Finalize()
{
	gameScene->Finish();
}
