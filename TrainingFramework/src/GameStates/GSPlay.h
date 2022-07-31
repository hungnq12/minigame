#pragma once
#include <fstream>
#include "GameStateBase.h"
#include "Unit.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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

	std::shared_ptr<SpriteAnimation> playerfx;
	std::shared_ptr<SpriteAnimation> enemyfx;

	enum BattleState { WIN, LOSE };
	BattleState state;

	void ReadFile();
	void WriteFile();

	void NewEnemy();
	void PlayerTurn();
	void PlayerAttack();
	void PlayerHeal();
	void EnemyTurn();
	void EnemyAttack();
	void EnemyHeal();
	void EndBattle();

	void PlayerHUD();
	void EnemyHUD();
	void Dialogue(std::string string);

	float PlayerTime = 0.0f;
	float EnemyTime = 0.0f;

	float StateWinTime = 0.0f;
	float StateLoseTime = 0.0f;

	int level = 1;

	bool playerTurn;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_panel;
	std::shared_ptr<Sprite2D>	m_hpbar;
	std::shared_ptr<Sprite2D>	m_hpbar1;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		m_gold;
	std::shared_ptr<Text>		m_stat;
	std::shared_ptr<Text>		m_stat1;
	std::shared_ptr<Text>		m_atk;
	std::shared_ptr<Text>		m_atk1;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

};

