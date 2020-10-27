#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy : public GameNode
{
private:
	FPOINT pos;
	int size;
	float speed;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void AutoMove();

	FPOINT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

