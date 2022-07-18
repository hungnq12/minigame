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
#include "Player.h"



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}
//auto model_c = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//auto shader_c = ResourceManagers::GetInstance()->GetShader("Animation");
//auto texture_c = ResourceManagers::GetInstance()->GetTexture("char_red_1.tga");
//auto model_bg = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//auto shader_bg = ResourceManagers::GetInstance()->GetShader("TextureShader");
//auto texture_bg = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
//auto model_b = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//auto shader_b = ResourceManagers::GetInstance()->GetShader("TextureShader");
//auto texture_b = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
//auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
//auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
std::shared_ptr<Player> obj1 = std::make_shared<Player>();

void GSPlay::Init()
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

	// score
	/*shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared<Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));*/

	// player
	auto model_c = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_c = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture_c = ResourceManagers::GetInstance()->GetTexture("char_red_1.tga");
	std::shared_ptr<Player> obj1 = std::make_shared<Player>(model_c, shader_c, texture_c, 8, 11, 1, 0.2f);
	obj1->Set2DPosition(150, 350);
	obj1->SetSize(160, 200);
	obj1->SetAtk(10);
	obj1->SetHp(100);
	obj1->SetDef(5);

	std::string t_atk = std::to_string(obj1->GetAtk());
	std::string t_hp = std::to_string(obj1->GetHp());
	std::string t_def = std::to_string(obj1->GetDef());

	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_stat = std::make_shared<Text>(shader_t, font, " atk: " + t_atk + " hp: " + t_hp + " def: " + t_def, TextColor::RED, 1.0);
	m_stat->Set2DPosition(Vector2(5, 25));

	m_listAnimation.push_back(obj1);
	m_KeyPress = 0;

	// player
	std::shared_ptr<Player> obj2 = std::make_shared<Player>(model_c, shader_c, texture_c, 8, 11, 1, 0.2f);
	obj2->Set2DPosition(650, 350);
	obj2->SetSize(160, 200);
	obj2->SetAtk(5);
	obj2->SetHp(20);
	obj2->SetDef(5);

	std::string t_atk1 = std::to_string(obj2->GetAtk());
	std::string t_hp1 = std::to_string(obj2->GetHp());
	std::string t_def1 = std::to_string(obj2->GetDef());

	m_stat1 = std::make_shared<Text>(shader_t, font, " atk: " + t_atk1 + " hp: " + t_hp1 + " def: " + t_def1, TextColor::RED, 1.0);
	m_stat1->Set2DPosition(Vector2(500, 25));

	m_listAnimation.push_back(obj2);
	m_KeyPress = 0;

	// button atk
	std::shared_ptr<GameButton>  button1 = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button1->Set2DPosition(Globals::screenWidth/2, Globals::screenHeight/2);
	button1->SetSize(50, 50);
	button1->SetOnClick([this]() {
		//obj1->Damage(2);
		GameStateMachine::GetInstance()->PerformStateChange();
		});
	m_listButton.push_back(button1);
	
	// button shop
	std::shared_ptr<GameButton>  button2 = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button2->Set2DPosition(Globals::screenWidth - 150, 50);
	button2->SetSize(50, 50);
	button2->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SHOP);
		});
	m_listButton.push_back(button2);
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