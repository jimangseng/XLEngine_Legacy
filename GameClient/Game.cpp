#include "Game.h"
#include "../XLEngine/XLEngine.h"

using namespace XL::GamePlay;

void Game::Start()
{
	Cube cube;

	cube.size = 0.8f;
	cube.color = XMFLOAT4{ 0.1f, 0.3f, 0.6f, 1.0f };	// �ϴ�
	cubes.emplace_back(cube);

	cube.size = 0.5f;
	cube.color = XMFLOAT4{ 0.6f, 0.1f, 0.1f, 1.0f };	// ����
	cubes.emplace_back(cube);

	cube.size = 0.3f;
	cube.color = XMFLOAT4{ 0.1f, 0.1f, 0.6f, 1.0f };	// �Ķ�
	cubes.emplace_back(cube);

	cube.size = 0.1f;
	cube.color = XMFLOAT4{ 0.5f, 0.5f, 0.2f, 1.0f };	// ���
	cube.Translate({ 0.0f, 0.3f, 0.0f });
	//cube.Yaw(30.0f);	// todo: Transform ����
	cubes.emplace_back(cube);

	scene.AddObject(cubes);

}

void Game::Update()
{
	// todo: Timer
	time += 0.02f;

	// todo: scene ������ �������� �ʵ��� ����
	scene.objects.at(0)->SetPosition({ 0.0f, sin(time), 0.0f });
	scene.objects.at(1)->SetPosition({ sin(time), 0.0f, 0.0f});
	scene.objects.at(2)->SetPosition({ cos(time), sin(time), 0.0f});
}

void Game::Finish()
{
}
