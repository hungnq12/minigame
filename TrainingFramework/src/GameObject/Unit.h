#pragma once
#include "SpriteAnimation.h"

class Unit : public SpriteAnimation
{
public:
	Unit(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	Unit(int level, int atk, int currentHP, int maxHP, int gold);
	Unit();
	~Unit();

	int level, atk, maxHP, currentHP, gold;

	void SetStat(int level, int atk, int currentHP, int maxHP, int gold);

	bool TakeDamage(int dmg);

	void Heal(int amount);

	void Reward(int level);

};
extern std::shared_ptr<Unit> playerUnit;