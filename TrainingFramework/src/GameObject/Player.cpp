#include "Player.h"
#include "Enemy.h"
Player::Player(int hp, int atk, int def)
{
	hp = 100;
	atk = 5;
	def = 10;
}
Player::~Player() 
{
}

void Player::Hit()
{
	Enemy::GetHit();
}

void Player::GetHit()
{

}