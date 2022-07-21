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

void Unit::SetStat(int atk, int currentHP, int maxHP)
{
	this->atk = atk;
	this->currentHP = currentHP;
	this->maxHP = maxHP;
}

bool Unit::TakeDamage(int dmg)
{
	currentHP -= dmg;

	if (currentHP <= 0)
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