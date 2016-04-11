#pragma once
#include "Firework.h"
class FireworkPool
{	
public:
	FireworkPool();
	FireworkPool(const FireworkPool&);
	FireworkPool& operator=(FireworkPool&);
	~FireworkPool();
	void Update(float dt);
	void AddFirework(float x, float y, 
		int level = 3, int shardsCount = 5, 
		Firework::FireworkType type = Firework::FireworkType::Common, bool isEnableCollision = true);
	void Draw();
private:
	std::vector<Firework*> _fireworks;
	bool _isCollisionEnabled;
};

