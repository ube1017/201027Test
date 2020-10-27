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

	// �̻���
	missile = new Missile();
	missile->Init();
	missile->SetPos(barrelEnd);

	return S_OK;
}

void Tank::Release()
{
	missile->Release();
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
		missile->Update();
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
		missile->Render(hdc);
	}
}

void Tank::Fire()
{
	if (missile)
	{
		if (missile->GetIsFire() == false)
		{
			// ��ġ
			missile->SetPos(barrelEnd);
			// ����
			missile->SetAngle(barrelAngle);
			// ����
			missile->SetIsFire(true);
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
