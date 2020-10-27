#pragma once
#include "GameNode.h"

class Tank;
class Enemy;
class MainGame : public GameNode
{
private:
	struct MouseData
	{
		int posX, posY;
		int clickedPosX, clickedPosY;
	};

	MouseData mouseData;
	HANDLE hTimer;

	Tank* tank1;
	Enemy* enemy1;

public:
	// 오버로딩
	// 오버라이딩

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool CheckRectCollision(RECT rc1, RECT rc2);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

