#include "stdafx.h"
#include "Shell.h"
const float LIFETIME_REDUCE_FACTOR = 0.8f;
const float SIZE_REDUCE_FACTOR = 0.8f;
const float GRAVITY_REDUCE_FACTOR = 0.25f;
Shell::Shell()
{
	posX = 0;
	posY = 0;
	_velX = 0;
	_velY = 0;
	_lifetime = 0;
	_size = 0;
	_timer = 0;
	_explosionSpeed = 0;
	_gravityAccel = 0;
	_isActive = false;
	isBlow = false;
}

Shell::~Shell()
{
	isBlow = false;
}
void Shell::Draw() 
{
	if (!_isActive) {
		return;
	}
  // ��� ������� �� ������ ��������
}
void Shell::Move(float dx, float dy)
{
	posX += dx;
	posY += dy;
}
void Shell::MoveTo(float x, float y)
{
	posX = x;
	posY = y;
}

void Shell::Update(float dt)
{
	if (!_isActive) {
		return;
	}
	_timer += dt;
	//����� �� ����������� ������� ������� ������
	if (_timer >= _lifetime )
	{
		MoveTo(_posX0 + _velX * _lifetime,
			_posY0 + _velY * _lifetime - _gravityAccel * _lifetime * _lifetime / 2); //��������� � �������� ����� ����������
		isBlow = true; //���������� ����, ����� ��������� ����� � ����������
	}
	else
	{
		//����������� �������
		Move(_velX * dt, (_velY - _gravityAccel * _timer) * dt);
	}
}
bool Shell::Blow(std::vector<Shell *> *shells, int indexToBlow)
{
	if (_currentExplosionLevel <= 0) // ���� ������ ���������, �� ������ ��������� ������
	{
		Deactivate();
	}
	else // ���� ������ ��������, �������� ������
	{
		float totalAngle = 360;
		for (int j = _shardsCount - 1; j >= 0; j--) // ����� � �����, ����� �� ������� �������� ���������� �������
		{
			// ��������� �������� �������
			FPoint speed;
			float angle = math::random(0.8f, 1.2f) * totalAngle * (1.f - (float)j / (float)(5));
			float kx = math::random(0.9f, 1.1f) * (cosf(angle * 2 * math::PI / totalAngle));
			float ky = math::random(0.9f, 1.1f) * (sinf(angle * 2 * math::PI / totalAngle));
			speed.x = kx * _explosionSpeed;
			speed.y = ky * _explosionSpeed;
			// ������������� ����� ��������� (������� � ��������, ����� �� ���� ������������� ������ �������,
			// ��� ��� ����� ������������ ��� ����� ��������� � ����� �����; ���������� ���������� - ��������� ����,
			// ��� ������� ����� ������ ������������� ������)
			shells[0][j + indexToBlow]->SetProperties(posX + 2 * _size * kx, 
				posY + 2 * _size * ky, speed,
				_currentExplosionLevel - 1, _shardsCount, 
				_lifetime * LIFETIME_REDUCE_FACTOR, _size * SIZE_REDUCE_FACTOR,
				_gravityAccel * GRAVITY_REDUCE_FACTOR, _explosionSpeed);
			shells[0][j + indexToBlow]->Activate();
		}
		isBlow = false;
		_timer = 0;
	}
	return _isActive;
}
void Shell::SetProperties(float x, float y, FPoint v, int explosionCharges,
	int shards, float lifetime, float size, float gravityAccel, float explSpeed)
{
	posX = x;
	posY = y;
	_velX = v.x;
	_velY = v.y;
	_lifetime = lifetime;
	_size = size;
	_shardsCount = shards;
	_explosionSpeed = explSpeed;
	_currentExplosionLevel = explosionCharges;
	_gravityAccel = gravityAccel;
}
void Shell::Activate()
{
	_posX0 = posX;
	_posY0 = posY;
	_isActive = true;
}