#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"


HRESULT Tank::Init()
{
	// 몸통
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;

	// 포신
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

	// 미사일
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
	// 미사일 발사 키입력
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
	{
		Fire();
	}

	// 포신 회전 키입력
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
	// 몸통
	//Rectangle(hdc, pos.x - (size / 2), pos.y - (size / 2),
	//	pos.x + (size / 2), pos.y + (size / 2));
	Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
		pos.x + (size / 2), pos.y + (size / 2));

	// 포신
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// 미사일
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
			// 위치
			missile->SetPos(barrelEnd);
			// 각도
			missile->SetAngle(barrelAngle);
			// 상태
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
