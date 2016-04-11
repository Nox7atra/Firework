#pragma once
#include "Shell.h"
#include "BeautifulShell.h"
class Firework
{
private:
	void CheckShell(int shellToBlowIndex);
	void BlowShell(int shellToBlowIndex);
	void InitShells();
public:
	enum FireworkType {
		Common = 0,
		Beautiful = 1
	};
	Firework();
	Firework(float x, float y, int level, int shardsCount, FireworkType type);
	~Firework();
	void Update(float dt);
	void Draw();
	void CheckCollisions(Firework *otherFirework);
	
	void LaunchFirstShell(float x, float y);

	bool IsFinished();
private:
	std::vector<Shell*> _shells;
	int _level;
	int _shardsCount;
	FireworkType _type;
	bool _isFinished;
	int _launchedShells;
};

