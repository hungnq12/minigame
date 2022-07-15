#pragma once
#include "SpriteAnimation.h"

class Player : public SpriteAnimation
{
public:
	Player() : SpriteAnimation() {}
	Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~Player();

};
