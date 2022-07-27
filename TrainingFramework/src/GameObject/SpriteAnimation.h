#pragma once
#include "BaseObject.h"
class SpriteAnimation : public BaseObject
{
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;
	GLint			m_numActions;
	GLint			m_currentAction;//index from 0 to m_numActions-1

public:
	SpriteAnimation() : BaseObject(), m_Vec2DPos(0), m_iHeight(0), m_iWidth(0), m_numFrames(0), m_currentFrame(0), m_frameTime(0), m_currentTime(0), m_numActions(0), m_currentAction(0) {}
	SpriteAnimation(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	SpriteAnimation(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		SetRotation(Vector3 rotation);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

	void SetCurrentAction(GLint x);
};

