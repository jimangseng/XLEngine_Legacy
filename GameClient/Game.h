#pragma once

#include "../XLEngine/GameScene.h"
class Game
{
public:
	Game() = default;
	~Game() = default;
	Game(const Game& rhs) = delete;
	Game& operator= (const Game& rhs) = delete;

public:
	void Start();
	void Update();
	void Finish();

public:
	XL::GamePlay::GameScene* GetScene() { return &scene; }

private:
	XL::GamePlay::GameScene scene;

	// todo: 타이머 제작
	float time = 0.0f;
};