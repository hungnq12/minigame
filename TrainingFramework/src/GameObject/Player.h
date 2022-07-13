#pragma once
#include "BaseObject.h"
#include <functional>
class Player:BaseObject 
{
public:
	int atk;
	Player(int hp, int atk, int def);
	~Player();
	void Hit();
	void GetHit();
};