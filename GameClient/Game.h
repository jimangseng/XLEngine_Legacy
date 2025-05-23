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
	void SetScene(XL::GamePlay::GameScene* _gameScene) { scene = *_gameScene; }

private:
	XL::GamePlay::GameScene scene;
};