#pragma once

#include <vector>
#include "../XLEngine/GameScene.h"
#include "../XLEngine/Cube.h"
class Game
{

public:
	void Start();
	void Update();
	void Finish();

public:
	XL::GamePlay::GameScene* GetScene() { return &scene; }

private:
	XL::GamePlay::GameScene scene;

	float time = 0.0f;
};