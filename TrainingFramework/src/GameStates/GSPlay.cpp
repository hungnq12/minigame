#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Unit.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	state = START;
	SetupBattle();
}

void GSPlay::SetupBattle()
{
	// background
	auto model_bg = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_bg = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_bg = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
	m_background = std::make_shared<Sprite2D>(model_bg, shader_bg, texture_bg);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	auto model_b = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_b = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_b = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// dialogue
	Dialogue("He is coming");

	// player
	auto model_c = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_c = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture_c = ResourceManagers::GetInstance()->GetTexture("char_red_1.tga");
	playerUnit = std::make_shared<Unit>(model_c, shader_c, texture_c, 8, 11, 1, 0.2f);
	playerUnit->Set2DPosition(150, 350);
	playerUnit->SetSize(160, 200);
	playerUnit->SetStat(5, 20, 20);

	PlayerHUD();

	m_listAnimation.push_back(playerUnit);
	m_KeyPress = 0;

	// enemy
	enemyUnit = std::make_shared<Unit>(model_c, shader_c, texture_c, 8, 11, 1, 0.2f);
	enemyUnit->Set2DPosition(650, 350);
	enemyUnit->SetSize(160, 200);
	enemyUnit->SetStat(5, 20, 20);

	EnemyHUD();

	m_listAnimation.push_back(enemyUnit);
	m_KeyPress = 0;

	//Sleep(500);

	state = PLAYERTURN;
	PlayerTurn();

	// button atk
	std::shared_ptr<GameButton>  button1 = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button1->Set2DPosition(Globals::screenWidth/2, Globals::screenHeight/2);
	button1->SetSize(50, 50);
	button1->SetOnClick([this]() {
		if (state != PLAYERTURN)
			return;

		PlayerAttack();
		});
	m_listButton.push_back(button1);
}
void GSPlay::PlayerAttack()
{
	bool isDead = enemyUnit->TakeDamage(playerUnit->atk);

	EnemyHUD();

	std::string number = std::to_string(playerUnit->atk);
	Dialogue("Player deal " + number + " damage");

	//Sleep(500);

	if (isDead)
	{
		state = WON;
		EndBattle();
	}
	else
	{
		state = ENEMYTURN;
		GSPlay::EnemyTurn();
	}
}

void GSPlay::EnemyTurn()
{
	Dialogue("He is attacking");

	//Sleep(200);

	bool isDead = playerUnit->TakeDamage(enemyUnit->atk);

	PlayerHUD();

	//Sleep(200);

	if (isDead)
	{
		state = LOST;
		EndBattle();
	}
	else
	{
		state = PLAYERTURN;
		GSPlay::PlayerTurn();
	}

}

void GSPlay::EndBattle()
{
	if (state == WON)
	{
		Dialogue("Win");
	}
	else if (state == LOST)
	{
		Dialogue("Lose");
	}
}
void GSPlay::PlayerTurn()
{
	Dialogue("Choose action");
}
void GSPlay::PlayerHUD()
{
	std::string t_atk = std::to_string(playerUnit->atk);
	std::string t_maxhp = std::to_string(playerUnit->maxHP);
	std::string t_curhp = std::to_string(playerUnit->currentHP);

	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_stat = std::make_shared<Text>(shader_t, font, " atk: " + t_atk + " hp: " + t_curhp + "/" + t_maxhp, TextColor::RED, 1.0);
	m_stat->Set2DPosition(Vector2(5, 25));
}
void GSPlay::EnemyHUD()
{
	std::string t_atk1 = std::to_string(enemyUnit->atk);
	std::string t_maxhp1 = std::to_string(enemyUnit->maxHP);
	std::string t_curhp1 = std::to_string(enemyUnit->currentHP);

	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_stat1 = std::make_shared<Text>(shader_t, font, " atk: " + t_atk1 + " hp: " + t_curhp1 + "/" + t_maxhp1, TextColor::RED, 1.0);
	m_stat1->Set2DPosition(Vector2(500, 25));
}
void GSPlay::Dialogue(std::string string)
{
	auto shader1 = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font1 = ResourceManagers::GetInstance()->GetFont("ARCADECLASSIC.ttf");
	m_score = std::make_shared< Text>(shader1, font1, string, Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_score->Set2DPosition(Vector2(60, 200));

	Sleep(500);
}
void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1<<3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	for (auto button1 : m_listButton)
	{
		if (button1->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	m_stat->Draw();
	m_stat1->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}