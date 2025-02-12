#include "GamePlayEngine.h"

#include <memory>
#include "GameObject.h"
#include "Cube.h"
#include "GameScene.h"

void XL::GamePlay::GamePlayEngine::Initialize()
{
	gameScene->Start();
}

void XL::GamePlay::GamePlayEngine::Update()
{
	gameScene->Update();
}

void XL::GamePlay::GamePlayEngine::Finalize()
{
	gameScene->Finish();
}
