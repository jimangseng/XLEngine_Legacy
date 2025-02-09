#include "GamePlayEngine.h"

#include <memory>
#include "IObject.h"
#include "Cube.h"
#include "GameScene.h"

void XL::GamePlayEngine::Initialize()
{
	scene->Start();
}

void XL::GamePlayEngine::Update()
{
	scene->Update();
}

void XL::GamePlayEngine::Finalize()
{
	scene->Finish();
}
