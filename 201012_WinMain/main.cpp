// main.cpp

/*
	Win32 API
	: Application Programming Interface
	�ü���� �������α׷� ������ ���� �����ش� �Լ��� ����

	�ϵ���� ----------�ü�� (Windows)---------- �������α׷�
						(API �Լ�)
*/

#include <Windows.h>
#include "MainGame.h"

// ��������
HINSTANCE	g_hInstance;	// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;			// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");
MainGame	g_mainGame;

void SetWindowSize(int startX, int startY, int sizeX, int sizeY);
void MakeRectangle(HDC hdc, int x, int y, int size);
void MakeStar(HDC hdc, int x, int y);

void MakeRectangle(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x, y);
}

void MakeStar(HDC hdc, int x, int y)
{
	MoveToEx(hdc, x, y, NULL);		// �׸��� ������ ��ġ�� ����
	LineTo(hdc, x + 30, y);
	LineTo(hdc, x + 5, y + 20);
	LineTo(hdc, x + 15, y - 10);
	LineTo(hdc, x + 25, y + 20);
	LineTo(hdc, x, y);
}

// ����Ʈ�� ��Ʈ�� �浹Ȯ��
bool IsInRect(RECT rc, POINT pt)
{
	//if (pt.x < rc.left || pt.x > rc.right 
	//	|| pt.y < rc.top || pt.y > rc.bottom)
	//{
	//	return false;
	//}

	//return true;


	// ���콺 x��ǥ�� left���� ũ�� &&
	// ���콺 x��ǥ�� right���� �۴� &&
	// ���콺 y��ǥ�� top���� ũ�� &&
	// ���콺 y��ǥ�� bottom���� �۴�
	if (rc.left < pt.x && pt.x < rc.right 
		&& rc.top < pt.y && pt.y < rc.bottom)
	{
		return true;
	}

	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// �����츦 �����ϱ� ���� �Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// ������ ������ ���� �⺻����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;	// ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50, 50, WINSIZE_X, WINSIZE_Y,
		NULL, NULL, g_hInstance, NULL);

	// ������ ���۾����� �缳��
	SetWindowSize(50, 50, WINSIZE_X, WINSIZE_Y);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	g_mainGame.Init();

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	g_mainGame.Release();


	return message.wParam;
}

// ������ �޼����� ó���ϴ� �Լ� (�ݹ��Լ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
	WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}

void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX; rc.bottom = sizeY;

	// ���� ������ ũ�� �޾ƿ´�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left,
		rc.bottom - rc.top, true);
}