#include "Missile.h"
#include "Enemy.h"


HRESULT Missile::Init()
{
	pos.x = 0;
	pos.y = 0;
	speed = 10.0f;
	size = 70;
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
		pos.x += cosf(DegreeToRadian(angle)) * speed;  //�̰������� ���� �����Ϸ縦���ȳ� ����
		pos.y -= sinf(DegreeToRadian(angle)) * speed;
		//���� �ε������� Ȯ��
		//������,�ަU 
		if (pos.x+(size/2) >= WINSIZE_X|| pos.x - (size / 2) <= 0)
		{
			angle = 180.0f - angle;
		}
		//��,�Ʒ�
		if (pos.y - (size / 2) <= 0||pos.y+ (size / 2) >=WINSIZE_Y)
		{
			angle = 360.0f - angle;
		}
		
		
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
