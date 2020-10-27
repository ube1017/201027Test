#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	hTimer = (HANDLE)SetTimer(
		g_hWnd,	// �������� �ڵ�
		0,		// �̺�Ʈ ���̵�
		10,		// ȣ�� �ֱ� ( ���� ȣ��Ǵ���? : WM_TIMER )
		NULL);	// ȣ���� �Լ��� ���

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

	// Ÿ�̸� ����
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
	//m1�� ������+ m2 �� ������ >= m1��m2������ �Ÿ� (->�浹)

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

// ��Ʈ�� ��Ʈ�� �浹Ȯ��
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
