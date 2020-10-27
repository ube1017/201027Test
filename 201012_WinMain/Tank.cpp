#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"


HRESULT Tank::Init()
{
	// ����
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;

	// ����
	barrelSize = 130;
	barrelEnd.x = WINSIZE_X / 2;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 90.0f;	// degree : 0 ~ 360 / radian : 0 ~ 6.28
	/*
		90 : 360 = x : 6.28
		360 * x = 6.28 * 90

		x = 90 * 6.28 / 360
		x = 90 * PI / 180
	*/
	missileCount = 5;
	// �̻���
	missile = new Missile[5];
	for (int i = 0; i < 5; i++)
	{
		missile[i].Init();
		missile[i].SetPos(barrelEnd);
	}

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Release();
	}
	delete missile;
}

void Tank::Update()
{
	// �̻��� �߻� Ű�Է�
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
	{
		Fire();
	}

	// ���� ȸ�� Ű�Է�
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		RotateBarrel(1.0f);
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		RotateBarrel(-1.0f);
	}

	if (missile)
	{
		for (int i = 0; i < 5; i++)
		{
			missile[i].Update();
		}
		
	}
}

void Tank::Render(HDC hdc)
{
	// ����
	//Rectangle(hdc, pos.x - (size / 2), pos.y - (size / 2),
	//	pos.x + (size / 2), pos.y + (size / 2));
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
		pos.x + (size / 2), pos.y + (size / 2));

	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
	if (missile)
	{
		for (int i = 0; i < 5; i++)
		{
			missile[i].Render(hdc);
		}
		
	}
}

void Tank::Fire()
{
	if (missile)
	{
		for (int i = 0; i < missileCount; i++)
		{
			if (missile[i].GetIsFire() == false)
			{
				// ��ġ
				missile[i].SetPos(barrelEnd);
				// ����
				missile[i].SetAngle(barrelAngle);
				// ����
				missile[i].SetIsFire(true);
			}
		}
	}
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;

	barrelEnd.x = pos.x
		+ cosf(DegreeToRadian(barrelAngle)) * barrelSize;
	barrelEnd.y = pos.y
		- sinf(DegreeToRadian(barrelAngle)) * barrelSize;;
}

void Tank::GetBarrelENd(FPOINT pos)
{
	//missile->SetPos = GetBarrelENd(barrelEnd);
}

void Tank::SetTarget(Enemy * target)
{
	this->target = target;
	if (missile)
	{
		missile->SetTarget(target);
	}
}

Tank::Tank()
{
}


Tank::~Tank()
{
}
