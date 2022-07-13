#pragma once
#include "BaseObject.h"
#include <functional>
class Enemy:BaseObject
{
public:
	int hp;
	Enemy(int hp, int atk, int def);
	~Enemy();
	void Hit();
	void GetHit();
};