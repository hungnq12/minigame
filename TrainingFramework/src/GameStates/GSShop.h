#pragma once
#include <fstream>
#include "GameStateBase.h"
#include "Unit.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSShop : public GameStateBase
{
public:
	GSShop();
	~GSShop();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_KeyPress;

	std::shared_ptr<Unit> playerUnit;
	std::shared_ptr<Unit> enemyUnit;

	void ReadFile();
	void WriteFile();

	void PlayerHUD();
	void Dialogue(std::string string);

	std::string level;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_panel;
	std::shared_ptr<Sprite2D>	m_hpbar;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		m_gold;
	std::shared_ptr<Text>		m_stat;
	std::shared_ptr<Text>		m_atk;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

};

