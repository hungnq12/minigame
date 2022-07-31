#include "GSMenu.h"
#include "Camera.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	ResourceManagers::GetInstance()->PlaySound("field_theme_1.wav", true, Globals::volumn);
	// background
	auto model_bg = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_bg = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_bg = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
	m_background = std::make_shared<Sprite2D>(model_bg, shader_bg, texture_bg);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// new game button
	auto model_b = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_b = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_b = ResourceManagers::GetInstance()->GetTexture("btn-newgame.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 75);
	button->SetOnClick([this]() {
		NewFile();
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		ResourceManagers::GetInstance()->StopSound("field_theme_1.wav");
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// load game button
	auto texture_bl = ResourceManagers::GetInstance()->GetTexture("btn-loadgame.tga");
	std::shared_ptr<GameButton> button1 = std::make_shared<GameButton>(model_b, shader_b, texture_bl);
	button1->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2+100);
	button1->SetSize(200, 75);
	button1->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		ResourceManagers::GetInstance()->StopSound("field_theme_1.wav");
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button1);

	//option button
	auto texture_b2 = ResourceManagers::GetInstance()->GetTexture("btn-option.tga");
	std::shared_ptr<GameButton> button2 = std::make_shared<GameButton>(model_b, shader_b, texture_b2);
	button2->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 200);
	button2->SetSize(200, 75);
	button2->SetOnClick([]() {
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		GameStateMachine::GetInstance()->PushState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(button2);

	// exit button
	texture_b = ResourceManagers::GetInstance()->GetTexture("btn-close.tga");
	button = std::make_shared<GameButton>(model_b, shader_b, texture_b);
	button->Set2DPosition(Globals::screenWidth - 100, 50);
	button->SetSize(100, 40);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// game title
	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("BreatheFireIii-PKLOB.ttf");
	m_textGameName = std::make_shared< Text>(shader_t, font, "MAGE KNIGHT", TextColor::RED, 3.0);
	m_textGameName->Set2DPosition(200, 200);
}
void GSMenu::NewFile()
{
	std::fstream f;
	f.open("..\\Data\\Players\\LoadGame.txt", std::ios::out);

	std::string data = "1\n5\n20\n20\n0\n2\n10\n10";

	f << data;

	f.close();
}
void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}
