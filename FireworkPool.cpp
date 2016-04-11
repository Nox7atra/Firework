#include "stdafx.h"
#include "FireworkPool.h"

FireworkPool::FireworkPool()
{
}
FireworkPool::~FireworkPool()
{
	for (int i = 0; i < _fireworks.size(); i++)
	{
		delete _fireworks[i];
	}
}
void FireworkPool::AddFirework(float x, float y, int level, 
	int shardsCount, Firework::FireworkType type, bool isEnableCollision)
{ 
	_isCollisionEnabled = isEnableCollision;
	_fireworks.push_back(new Firework(x, y, level, shardsCount, type));
}
void FireworkPool::Update(float dt)
{
	for (int i = _fireworks.size() - 1; i >= 0; i--)
	{
		//Если коллизия включена, проверяем коллизию между фейерверками
		if (_isCollisionEnabled) 
		{
			for (int j = i - 1; j >= 0; j--)
			{
				_fireworks[i]->CheckCollisions(_fireworks[j]);
			}
		}
		_fireworks[i]->Update(dt);
		//Если закончился, то убиваем его
		if (_fireworks[i]->IsFinished())
		{
			delete _fireworks[i];
			_fireworks.erase(_fireworks.begin() + i);
		}
	}
}
void FireworkPool::Draw()
{
	for (int i = 0; i < _fireworks.size(); i++)
	{
		_fireworks[i]->Draw();
	}
}