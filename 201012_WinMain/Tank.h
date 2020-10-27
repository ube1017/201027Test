#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Tank : public GameNode
{
private:
	// 个烹 谅钎, 农扁
	FPOINT pos;
	int size;

	// 器脚
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 固荤老
	Missile* missile;
	int missileCount;

	// 利(鸥百)
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

