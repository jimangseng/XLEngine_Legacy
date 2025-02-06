#include "GamePlayEngine.h"

#include <memory>
#include "IObject.h"
#include "Cube.h"
#include "GameScene.h"

void XL::GamePlayEngine::Initialize()
{
	scene = new XL::GamePlay::GameScene();

	// scene setting
	shared_ptr<Cube> cube;

	cube = make_shared<Cube>();
	cube->size = 0.8f;
	cube->color = XMFLOAT4{ 0.0f, 0.5f, 1.0f, 1.0f };	// ÇÏ´Ã
	scene->AddObject(cube);

	cube = make_shared<Cube>();
	cube->size = 0.5f;
	cube->color = XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f };	// »¡°­
	scene->AddObject(cube);

	cube = make_shared<Cube>();
	cube->size = 0.3f;
	cube->color = XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f };	// ÆÄ¶û
	scene->AddObject(cube);

	cube = make_shared<Cube>();
	cube->size = 0.1f;
	cube->color = XMFLOAT4{ 1.0f, 1.0f, 0.0f, 1.0f };	// ³ë¶û
	cube->Translate({ 1.0f, 0.0f, 0.0f });
	scene->AddObject(cube);

	// 
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
