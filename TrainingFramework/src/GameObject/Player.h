#pragma once
#include "Sprite2D.h"
class Player : public Sprite2D
{
public:
	Player();
	~Player();
protected:
	void Attack();
private:
	int hp, atk, def;
};