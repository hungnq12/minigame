#include "Player.h"

Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetAtk(GLint atk)
{
	this->atk = atk;
}
GLint Player::GetAtk()
{
	return atk;
}
void Player::SetHp(GLint hp)
{
	this->hp = hp;
}
GLint Player::GetHp()
{
	return hp;
}
void Player::SetDef(GLint def)
{
	this->def = def;
}
GLint Player::GetDef()
{
	return def;
}

void Player::Damage(GLint dame)
{
	this->hp = this->hp - dame;
}
