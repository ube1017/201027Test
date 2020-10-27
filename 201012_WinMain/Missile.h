#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Missile : public GameNode
{
private:
	// �ӵ�, ��ǥ, ũ��, �߻翩��
	float speed;
	FPOINT pos;
	int size;
	bool isFire;
	float angle;
	float destAngle;
	Enemy* target;
	float followRatio;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }

	void SetPos(FPOINT pos) { this->pos = pos; }

	void SetAngle(float angle) { this->angle = angle; }

	void SetTarget(Enemy* target) { this->target = target; }

	Missile();
	~Missile();
};

