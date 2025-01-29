#include "../XLEngine/XLEngine.h"

#pragma comment (lib, "XLEngine.lib")

class Game
{
public:
	
	unique_ptr<XLEngine> engine;
	
	void Start(HWND _hWnd)
	{
		engine = make_unique<XLEngine>(_hWnd);
		engine->Initialize();
	}

	void Update()
	{
		engine->Update();
	}

	void Finish()
	{
		engine->Finish();
	}
};