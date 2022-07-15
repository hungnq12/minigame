#include "Player.h"

Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Player::~Player()
{
}