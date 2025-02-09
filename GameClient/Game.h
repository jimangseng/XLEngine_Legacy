#pragma once

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
	std::vector<Cube> cubes;

	float time = 0.0f;
};