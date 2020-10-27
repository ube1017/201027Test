#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	hTimer = (HANDLE)SetTimer(
		g_hWnd,	// 윈도우의 핸들
		0,		// 이벤트 아이디
		10,		// 호출 주기 ( 뭐가 호출되는지? : WM_TIMER )
		NULL);	// 호출할 함수를 등록

	tank1 = new Tank();
	tank1->Init();

	enemy1 = new Enemy();
	enemy1->Init();

	tank1->SetTarget(enemy1);


	return S_OK;
}

void MainGame::Release()
{
	enemy1->Release();
	delete enemy1;

	tank1->Release();
	delete tank1;

	// 타이머 삭제
	KillTimer(g_hWnd, 0);

	KeyManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	if (tank1)
	{
		tank1->Update();
	}

	if (enemy1)	enemy1->Update();
	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	if (tank1)
	{
		tank1->Render(hdc);
	}
	if (enemy1) enemy1->Render(hdc);

	char szText[128] = "";
	wsprintf(szText, "X : %d, Y : %d", mouseData.posX, mouseData.posY);
	TextOut(hdc, mouseData.posX, mouseData.posY, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdc, 10, 30, szText, strlen(szText));

}

bool MainGame::CheckCollision(Missile * m1, Missile * m2)
{
	//m1의 반지름+ m2 의 반지름 >= m1과m2사이의 거리 (->충돌)

	return false;
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;


	switch (iMessage)
	{
	case WM_TIMER:
		//(*this).Update();
		this->Update();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_MOUSEMOVE:
		mouseData.posX = LOWORD(lParam);
		mouseData.posY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

// 렉트와 렉트의 충돌확인
bool MainGame::CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right ||
		rc1.right < rc2.left ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
	{
		return false;
	}

	return true;
}

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}
