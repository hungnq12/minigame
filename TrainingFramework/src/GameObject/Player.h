#pragma once
#include "SpriteAnimation.h"

class Player : public SpriteAnimation 
{
protected:
	GLint atk, hp, def;
public:
	Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~Player();

	void SetAtk(GLint atk);
	GLint GetAtk();

	void SetHp(GLint hp);
	GLint GetHp();

	void SetDef(GLint def);
	GLint GetDef();

	void Damage(GLint dame);
};
