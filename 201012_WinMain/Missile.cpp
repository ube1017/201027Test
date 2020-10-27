#include "Missile.h"
#include "Enemy.h"


HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	speed = 1.0f;
	size = 20;
	isFire = false;
	angle = 0.0f;
	destAngle = 0.0f;
	target = nullptr;
	followRatio = 0.1f;

	return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	if (isFire)
	{
		float tempAngle;
		if (target)
		{
			followRatio += 0.4f;
			if (followRatio >= 100.0f)
			{
				followRatio = 100.0f;
			}

			destAngle = atan2(-(target->GetPos().y - pos.y),
				target->GetPos().x - pos.x);

			tempAngle = DegreeToRadian(angle);
			tempAngle += (destAngle - DegreeToRadian(angle)) / (100.0f / followRatio);
			angle = RadianToDegree(tempAngle);
		}
		pos.x += cosf(tempAngle) * speed;
		pos.y -= sinf(tempAngle) * speed;

		//pos.x += cosf(DegreeToRadian(angle)) * speed;
		//pos.y -= sinf(DegreeToRadian(angle)) * speed;
	}
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2),
			pos.x + (size / 2), pos.y + (size / 2));
	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
