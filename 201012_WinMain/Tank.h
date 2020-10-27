#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Tank : public GameNode
{
private:
	// ���� ��ǥ, ũ��
	FPOINT pos;
	int size;

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���
	Missile* missile;
	int missileCount;

	// ��(Ÿ��)
	Enemy* target;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Fire();
	void RotateBarrel(float angle);
	void GetBarrelENd(FPOINT pos);
	void SetTarget(Enemy* target);

	Tank();
	~Tank();
};

