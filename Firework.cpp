#include "stdafx.h"
#include "Firework.h"

const float FIREWORK_START_SPEED = 300;
const float SHELL_LIFETIME = 1.8f;
const float SHELL_SIZE = 6;
const float SHELL_EXPLOSION_SPEED = 75;
const float SHELL_GRAVITY_ACCELERATION = 120;

Firework::Firework()
{
	_launchedShells = 0;
	_isFinished = false;
	_type = FireworkType::Common;
}
Firework::Firework(float x, float y, int level, int shardsCount, FireworkType type)
{
	_shells = std::vector<Shell*>(pow(shardsCount, level));
	_level = level;
	_shardsCount = shardsCount;
	_isFinished = false;
	_type = type;
	InitShells();
	LaunchFirstShell(x, y);
}
Firework::~Firework()
{
	for (int i = 0; i < _shells.size(); i++) 
	{
		delete _shells[i];
	}
}
//�������� ������ ��� ������ �������
void Firework::InitShells()
{
	for (int i = 0; i < _shells.size(); i++)
	{
		switch (_type)
		{
		case Firework::Common:
			_shells[i] = new Shell();
			break;
		case Firework::Beautiful:
			//_shells[i] = new BeautifulShell(); (class BeautifulShell:Shell)
			break;
		default:
			_shells[i] = new Shell();
			break;
		}
	}
}
void Firework::LaunchFirstShell(float x, float y)
{
	_shells[0]->SetProperties(x, y, FPoint(0, FIREWORK_START_SPEED), _level,
		_shardsCount, SHELL_LIFETIME, SHELL_SIZE, SHELL_GRAVITY_ACCELERATION, SHELL_EXPLOSION_SPEED);
	_shells[0]->Activate();
	_launchedShells = 1;
}
void Firework::Update(float dt)
{
	for (int i = _launchedShells - 1; i >= 0; i--)
	{
		_shells[i]->Update(dt);
	}
	//�������� ���� �� ��� ��������
	for (int i = _launchedShells - 1; i >= 0; i--)
	{
		CheckShell(i);
	}
}
void Firework::Draw()
{
	for (int i = 0; i < _launchedShells; i++)
	{
		_shells[i]->Draw();
	}
}

void Firework::CheckShell(int shellToBlowIndex)
{
	if (_shells[shellToBlowIndex]->isBlow)
	{
		BlowShell(shellToBlowIndex);
	}
}
void Firework::BlowShell(int shellToBlowIndex)
{
	int newLaunched = _launchedShells;

	//�������� ���������� ������� ��������� ����� ���������� 
	Shell* tmpShell = _shells[shellToBlowIndex];
	_shells[shellToBlowIndex] = _shells[_launchedShells - 1];
	_shells[_launchedShells - 1] = tmpShell;

	//��������
	bool isBlowed = _shells[_launchedShells - 1]->Blow(&_shells, _launchedShells - 1);

	//���� ���������, ������������� ����� �������� ��������
	if (isBlowed)
	{
		newLaunched = _launchedShells + _shells[_launchedShells - 1]->GetShardsCount() - 1;
	}

	_launchedShells = newLaunched;
}
int CompareShells(const void * first, const void * second) //���������� ��� ����������
{
	if ((Shell*)first > (Shell*)second) return 1;
	if ((Shell*)first == (Shell*)second) return 0;
	if ((Shell*)first < (Shell*)second) return -1;
}
void Firework::CheckCollisions(Firework *otherFirework)
{
	//C�������� ������� � ������� ����������� ���������� �
	std::qsort(&_shells[0], _launchedShells, sizeof(Shell*), CompareShells);
	std::qsort(&(otherFirework->_shells[0]), otherFirework->_launchedShells, sizeof(Shell*), CompareShells);
	for (int i = _launchedShells - 1; i >= 0; i--)
	{
		for (int j = otherFirework->_launchedShells - 1; j >= 0; j--)
		{
			//��� ��� ���������� �������������, ������� �� �����, ����� ��������� � ������� ������� �����
			//������ ������� �� ���������� �������, ��� ������ �������� �����
			if (std::fabs(_shells[i]->posX - otherFirework->_shells[j]->posX) > _shells[i]->GetSize() / 2
				&& _shells[i]->posX < otherFirework->_shells[j]->posX)
			{
				break;
			}
			//�������� �� �������������� �������� �����
			if (std::fabs(_shells[i]->posX - otherFirework->_shells[j]->posX) <
				(_shells[i]->GetSize() + otherFirework->_shells[i]->GetSize()) / 2 &&
				std::fabs(_shells[i]->posY - otherFirework->_shells[j]->posY) < 
				(_shells[i]->GetSize() + otherFirework->_shells[i]->GetSize()) / 2)
			{
				_shells[i]->isBlow = true;
				otherFirework->_shells[j]->isBlow = true;
			}
		}
	}
}
bool Firework::IsFinished()
{
	_isFinished = false;
	//��������� ���� �� ��������, ���� ���, �� ����������� ���������
	for (int i = 0; i < _launchedShells; i++)
	{
		_isFinished = _isFinished || _shells[i]->IsActive();
		if (_shells[i]->IsActive())
		{
			break;
		}
	}
	return !_isFinished;
}