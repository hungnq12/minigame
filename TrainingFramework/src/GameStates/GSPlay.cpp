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


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	ResourceManagers::GetInstance()->PlaySound("Track_#1.wav", true, Globals::volumn);

	// background
	auto model_bg = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_bg = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_bg = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
	m_background = std::make_shared<Sprite2D>(model_bg, shader_bg, texture_bg);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button option
	auto model_b = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_b = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_b = ResourceManagers::GetInstance()->GetTexture("btn-option.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button->Set2DPosition(Globals::screenWidth/2, 40);
	button->SetSize(100, 40);
	button->SetOnClick([this]() {
		WriteFile();
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		ResourceManagers::GetInstance()->StopSound("Track_#1.wav");
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(button);


	// shop
	auto texture_bs = ResourceManagers::GetInstance()->GetTexture("btn-shop.tga");
	std::shared_ptr<GameButton> btn_shop = std::make_shared<GameButton>(model_b, shader_b, texture_bs);
	btn_shop->Set2DPosition(Globals::screenWidth/2, 90);
	btn_shop->SetSize(100, 40);
	btn_shop->SetOnClick([this]() {
		WriteFile();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SHOP);
		});
	m_listButton.push_back(btn_shop);


	// dialogue
	auto texture_pn = ResourceManagers::GetInstance()->GetTexture("panel.tga");
	m_panel = std::make_shared<Sprite2D>(model_bg, shader_bg, texture_pn);
	m_panel->Set2DPosition(Globals::screenWidth/2, Globals::screenHeight-50);
	m_panel->SetSize(850, 150);
	Dialogue("Monster da den");

	// player
	auto model_c = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_c = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture_c = ResourceManagers::GetInstance()->GetTexture("char_red_1.tga");
	playerUnit = std::make_shared<Unit>(model_c, shader_c, texture_c, 8, 5, 4, 0.2f);
	playerUnit->Set2DPosition(150, 400);
	playerUnit->SetSize(160, 200);

	m_listAnimation.push_back(playerUnit);
	m_KeyPress = 0;


	//
	auto texture_cpf = ResourceManagers::GetInstance()->GetTexture("strike.tga");
	playerfx = std::make_shared<SpriteAnimation>(model_c, shader_c, texture_cpf, 6, 1, 1, 0.2f);
	playerfx->Set2DPosition(670, 380);
	playerfx->SetSize(350, 150);
	m_listAnimation.push_back(playerfx);

	// enemy
	auto texture_ce = ResourceManagers::GetInstance()->GetTexture("Wizard.tga");
	enemyUnit = std::make_shared<Unit>(model_c, shader_c, texture_ce, 5, 5, 4, 0.2f);
	enemyUnit->Set2DPosition(650, 330);
	enemyUnit->SetSize(550, 600);

	m_listAnimation.push_back(enemyUnit);
	m_KeyPress = 0;

	ReadFile();
	PlayerHUD();
	EnemyHUD();

	//
	auto texture_cef = ResourceManagers::GetInstance()->GetTexture("fire.tga");
	enemyfx = std::make_shared<SpriteAnimation>(model_c, shader_c, texture_cef, 12, 1, 1, 0.2f);
	enemyfx->Set2DPosition(150, 380);
	enemyfx->SetSize(160, 200);
	m_listAnimation.push_back(enemyfx);

	// button atk
	auto texture_b_atk = ResourceManagers::GetInstance()->GetTexture("btn-attack.tga");
	std::shared_ptr<GameButton>  btn_atk = std::make_shared<GameButton>(model_b, shader_b, texture_b_atk);
	btn_atk->Set2DPosition(520, 550);
	btn_atk->SetSize(100, 40);
	btn_atk->SetOnClick([this]() {
		if (EnemyTime != 0.0f)
			return;
		PlayerAttack();
		});
	m_listButton.push_back(btn_atk);

	// button heal
	auto texture_b_heal = ResourceManagers::GetInstance()->GetTexture("btn-heal.tga");
	std::shared_ptr<GameButton>  btn_heal = std::make_shared<GameButton>(model_b, shader_b, texture_b_heal);
	btn_heal->Set2DPosition(650, 550);
	btn_heal->SetSize(100, 40);
	btn_heal->SetOnClick([this]() {
		if (EnemyTime != 0.0f)
			return;
		PlayerHeal();
		});
	m_listButton.push_back(btn_heal);

	PlayerTurn();
}
void GSPlay::NewEnemy()
{
	playerUnit->Reward(level);
	PlayerHUD();
	level+=2;

	if(level==6) GameStateMachine::GetInstance()->ChangeState(StateType::STATE_WIN);

	Dialogue("New enemy");

	enemyUnit->SetStat(level, level, level*3, level*3, 0);

	EnemyHUD();

	PlayerTurn();
}
void GSPlay::PlayerAttack()
{
	enemyUnit->SetCurrentAction(2);
	playerUnit->SetCurrentAction(3);

	playerfx->SetCurrentAction(0);
	ResourceManagers::GetInstance()->PlaySound("sword.wav", false, Globals::volumn);
	bool isDead = enemyUnit->TakeDamage(playerUnit->atk);

	EnemyHUD();

	std::string number = std::to_string(playerUnit->atk);
	Dialogue("Player deal " + number + " damage");

	if (isDead)
	{
		enemyUnit->SetCurrentAction(1);
		state = WIN;
		StateWinTime += 2.0f;
		EndBattle();
		playerUnit->atk++;

	}
	else
	{
		EnemyTime += 1.5f;
		/*EnemyTurn();*/
	}
}
void GSPlay::PlayerHeal()
{
	playerUnit->Heal(playerUnit->atk);

	PlayerHUD();

	std::string number = std::to_string(playerUnit->atk);
	Dialogue("Player heal 5 hp");

	EnemyTime += 1.5f;
}
void GSPlay::PlayerTurn()
{
	playerTurn = true;
	enemyUnit->SetCurrentAction(4);
	playerUnit->SetCurrentAction(4);
	enemyfx->SetCurrentAction(1);
	playerfx->SetCurrentAction(1);
	Dialogue("Choose action");
}
void GSPlay::EnemyTurn()
{
	playerTurn = false;
	enemyUnit->SetCurrentAction(4);
	playerUnit->SetCurrentAction(4);
	enemyfx->SetCurrentAction(1);
	playerfx->SetCurrentAction(1);
	if (enemyUnit->currentHP < enemyUnit->maxHP / 3) EnemyHeal();
	else EnemyAttack();
}
void GSPlay::EnemyAttack()
{
	playerUnit->SetCurrentAction(2);
	enemyUnit->SetCurrentAction(3);
	enemyfx->SetCurrentAction(0);
	ResourceManagers::GetInstance()->PlaySound("fire.wav", false, Globals::volumn);
	bool isDead = playerUnit->TakeDamage(enemyUnit->atk);

	PlayerHUD();

	std::string number = std::to_string(enemyUnit->atk);
	Dialogue("Enemy deal " + number + " damage");

	if (isDead)
	{
		playerUnit->SetCurrentAction(1);
		state = LOSE;
		StateLoseTime += 1.0f;
		EndBattle();
	}
	else
	{
		PlayerTime += 1.5f;
		/*PlayerTurn();*/
	}

}
void GSPlay::EnemyHeal()
{
	enemyUnit->Heal(enemyUnit->atk/3);

	EnemyHUD();

	std::string number = std::to_string(playerUnit->atk);
	Dialogue("Enemy heal 1 hp");

	PlayerTime += 1.5f;
}
void GSPlay::EndBattle()
{
	if (state == WIN)
	{
		Dialogue("Win");
	}
	else if (state == LOSE)
	{
		Dialogue("Lose");
	}
}
void GSPlay::PlayerHUD()
{
	std::string t_atk = std::to_string(playerUnit->atk);
	std::string t_maxhp = std::to_string(playerUnit->maxHP);
	std::string t_curhp = std::to_string(playerUnit->currentHP);
	std::string t_gold = std::to_string(playerUnit->gold);

	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("PixelGameFont.ttf");
	m_stat = std::make_shared<Text>(shader_t, font, t_curhp + "/" + t_maxhp, TextColor::WHITE, 0.7);
	m_stat->Set2DPosition(100,45);

	m_atk = std::make_shared<Text>(shader_t, font, t_atk, TextColor::WHITE, 1.2);
	m_atk->Set2DPosition(45, 65);

	m_gold = std::make_shared<Text>(shader_t, font, t_gold + " coin", TextColor::WHITE, 1.0);
	m_gold->Set2DPosition(150, 90);

	std::string grade_str = "";
		float grade = (float) playerUnit->currentHP/playerUnit->maxHP;
		if (grade >= 1) grade_str = "10";
		else if (grade >= 0.9) grade_str = "9";
		else if (grade >= 0.8) grade_str = "8";
		else if (grade >= 0.7) grade_str = "7";
		else if (grade >= 0.6) grade_str = "6";
		else if (grade >= 0.5) grade_str = "5";
		else if (grade >= 0.4) grade_str = "4";
		else if (grade >= 0.3) grade_str = "3";
		else if (grade >= 0.2) grade_str = "2";
		else if (grade >= 0.1) grade_str = "1";
		else grade_str = "0";
	auto model_hp = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_hp = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_hp = ResourceManagers::GetInstance()->GetTexture("HP" + grade_str + ".tga");
	m_hpbar = std::make_shared<Sprite2D>(model_hp, shader_hp, texture_hp);
	m_hpbar->Set2DPosition(260, 100);
	m_hpbar->SetSize(620, 460);
}
void GSPlay::EnemyHUD()
{
	std::string t_atk1 = std::to_string(enemyUnit->atk);
	std::string t_maxhp1 = std::to_string(enemyUnit->maxHP);
	std::string t_curhp1 = std::to_string(enemyUnit->currentHP);

	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("PixelGameFont.ttf");
	m_stat1 = std::make_shared<Text>(shader_t, font, t_curhp1 + "/" + t_maxhp1, TextColor::WHITE, 0.7);
	m_stat1->Set2DPosition(640, 45);

	m_atk1 = std::make_shared<Text>(shader_t, font, t_atk1, TextColor::WHITE, 1.2);
	m_atk1->Set2DPosition(730, 65);

	std::string grade_str = "";
	float grade = (float) enemyUnit->currentHP / enemyUnit->maxHP;
	if (grade >= 1) grade_str = "10";
	else if (grade >= 0.9) grade_str = "9";
	else if (grade >= 0.8) grade_str = "8";
	else if (grade >= 0.7) grade_str = "7";
	else if (grade >= 0.6) grade_str = "6";
	else if (grade >= 0.5) grade_str = "5";
	else if (grade >= 0.4) grade_str = "4";
	else if (grade >= 0.3) grade_str = "3";
	else if (grade >= 0.2) grade_str = "2";
	else if (grade >= 0.1) grade_str = "1";
	else grade_str = "0";
	auto model_hp = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_hp = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_hp = ResourceManagers::GetInstance()->GetTexture("HPe"+grade_str+".tga");
	m_hpbar1 = std::make_shared<Sprite2D>(model_hp, shader_hp, texture_hp);
	m_hpbar1->Set2DPosition(540, 100);
	m_hpbar1->SetSize(620, 460);;
}
void GSPlay::Dialogue(std::string string)
{
	auto shader1 = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font1 = ResourceManagers::GetInstance()->GetFont("Fool.ttf");
	m_score = std::make_shared< Text>(shader1, font1, string, Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.5f);
	m_score->Set2DPosition(100, 560);
}
void GSPlay::ReadFile()
{
	std::fstream f;
	f.open("..\\Data\\Players\\LoadGame.txt", std::ios::in);
	std::string line_str;
	int line;
	int i = 1;
	while (!f.eof())          
	{
		getline(f, line_str); 
		line = stoi(line_str);
		switch (i)
		{
			case 1:
				playerUnit->level = line;
			case 2:
				playerUnit->atk = line;
			case 3:
				playerUnit->currentHP = line;
			case 4:
				playerUnit->maxHP = line;
			case 5:
				playerUnit->gold = line;
			case 6:
				enemyUnit->atk = line;
			case 7:
				enemyUnit->currentHP = line;
			case 8:
				enemyUnit->maxHP = line;
		}
		i++;
	}
	f.close();
}
void GSPlay::WriteFile()
{
	std::fstream f; 
	f.open("..\\Data\\Players\\LoadGame.txt", std::ios::out);

	std::string t_level = std::to_string(playerUnit->level);
	std::string t_atk = std::to_string(playerUnit->atk);
	std::string t_maxhp = std::to_string(playerUnit->maxHP);
	std::string t_curhp = std::to_string(playerUnit->currentHP);
	std::string t_gold = std::to_string(playerUnit->gold);
	std::string t_atk1 = std::to_string(enemyUnit->atk);
	std::string t_maxhp1 = std::to_string(enemyUnit->maxHP);
	std::string t_curhp1 = std::to_string(enemyUnit->currentHP);

	std::string data = t_level + "\n" + t_atk + "\n" + t_curhp + "\n" + t_maxhp + "\n" + t_gold + "\n" + t_atk1 + "\n" + t_curhp1 + "\n" + t_maxhp1;

	f << data;                            

	f.close();
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
	if (EnemyTime > 0.0f)
	{
		EnemyTime -= deltaTime;
		if (EnemyTime < 0.0f)
		{
			EnemyTime = 0.0f;
			EnemyTurn();
		}
	}
	if (PlayerTime > 0.0f)
	{
		PlayerTime -= deltaTime;
		if (PlayerTime < 0.0f)
		{
			PlayerTime = 0.0f;
			PlayerTurn();
		}
	}
	if (StateLoseTime > 0.0f)
	{
		StateLoseTime -= deltaTime;
		if (StateLoseTime < 0.0f)
		{
			StateLoseTime = 0.0f;
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		}
	}
	if (StateWinTime > 0.0f)
	{
		StateWinTime -= deltaTime;
		if (StateWinTime < 0.0f)
		{
			StateWinTime = 0.0f;
			NewEnemy();
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_panel->Draw();
	if (enemyUnit->currentHP > 0)
	{
		m_hpbar1->Draw();
		m_stat1->Draw();
		m_atk1->Draw();

	}
	if (playerUnit->currentHP > 0)
	{
		m_hpbar->Draw();
		m_stat->Draw();
		m_atk->Draw();
		m_gold->Draw();
	}
	m_score->Draw();
	if (playerTurn == true)
	{
		for (auto it : m_listButton)
		{
			it->Draw();
		}
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}