#include "Unit.h"

Unit::Unit(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::SetPlayerStat(int level)
{
	this->level = level;
	this->atk = level * 5;
	this->currentHP = level * 10;
	this->maxHP = level * 10;
}

void Unit::SetEnemyStat(int level)
{
	this->level = level;
	this->atk = level * 2;
	this->currentHP = level * 7;
	this->maxHP = level * 7;
}

bool Unit::TakeDamage(int dmg)
{
	currentHP -= dmg;
	if (currentHP < 0) 
		currentHP = 0;
	if (currentHP == 0)
		return true;
	else
		return false;
}

void Unit::Heal(int amount)
{
	currentHP += amount;
	if (currentHP > maxHP)
		currentHP = maxHP;
}

void Unit::Reward(int level)
{
	this->atk += level;
	this->currentHP += (level * 2);
	this->maxHP += (level * 2);
	this->gold += (level * 10);

}