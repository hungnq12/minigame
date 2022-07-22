#pragma once
#include "SpriteAnimation.h"

class Unit : public SpriteAnimation 
{
public:
	Unit(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	Unit();
	~Unit();

	int level, atk, maxHP, currentHP;

	int gold = 0;

	void SetPlayerStat(int level);

	void SetEnemyStat(int level);

	bool TakeDamage(int dmg);

	void Heal(int amount);

	void Reward(int level);
};
