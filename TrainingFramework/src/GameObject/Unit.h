#pragma once
#include "SpriteAnimation.h"

class Unit : public SpriteAnimation 
{
public:
	Unit(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	Unit();
	~Unit();

	int atk, maxHP, currentHP;

	void SetStat(int atk, int currentHP, int maxHP);

	bool TakeDamage(int dmg);

	void Heal(int amount);
};
