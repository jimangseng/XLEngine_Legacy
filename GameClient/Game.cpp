#include "../XLEngine/XLEngine.h"

#pragma comment (lib, "XLEngine.lib")

class Game
{
public:
	unique_ptr<XLEngine> engine;

	Game(HWND _hWnd)
		: engine(make_unique<XLEngine>(_hWnd))
	{

	}
	void Start()
	{
		engine->Initialize();
	}

	void Update()
	{
		engine->Update();
	}

	void Finalize()
	{
		engine->Finalize();
	}
};