#pragma once
#include "pch.h"
#include "Singleton.h"
#include <bitset>

using namespace std;
#define KEY_MAX_COUNT	256

class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<KEY_MAX_COUNT>	keyUp;
	bitset<KEY_MAX_COUNT>	keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	// Ű�� ó�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);		// Ű�� ���ȴٰ� �������� �Ǵ�
	bool IsStayKeyDown(int key);	// Ű�� ������ �ִ��� �Ǵ�

	void SetKeyDown(int key, bool state) { keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { keyUp.set(key, state); }

	bitset<KEY_MAX_COUNT> GetKeyDown() { return keyDown; }
	bitset<KEY_MAX_COUNT> GetKeyUp() { return keyUp; }

	KeyManager();
	~KeyManager();
};

