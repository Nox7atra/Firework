#pragma once
#include <vector>
class Shell
{

protected:
	void Deactivate() { _isActive = false; }
public:
	Shell();
	const float GetSize() const { return _size; }
	const float GetShardsCount() const { return _shardsCount; }
	const bool IsActive() const { return _isActive; }
	void Activate();
	void Move(float dx, float dy);
	void MoveTo(float x, float y);
	virtual ~Shell();
	virtual bool Blow(std::vector<Shell *> *shells, int startIndex);
	virtual void SetProperties(float x, float y, FPoint v, int explosionCharges,
		int shards, float lifetime, float size, float gravityAccel, float explSpeed);
	virtual void Draw();
	virtual void Update(float dt);

	//Операторы перегружены только ради сортировки по координате Х
	virtual const bool operator>(Shell* other)
	{
		return this->posX > other->posX;
	}
	virtual const bool operator==(Shell* other)
	{
		return this->posX == other->posX;
	}
	virtual const bool operator<(Shell* other)
	{
		return this->posX < other->posX;
	}
protected:
	float _size;
	float _posX0;
	float _posY0;
	float _velX;
	float _velY;
	float _gravityAccel;
	float _timer;
	float _lifetime;
	float _explosionSpeed;
	int _currentExplosionLevel;
	int _shardsCount;
	bool _isActive;

public:
	float posX;
	float posY;
	bool isBlow;
};