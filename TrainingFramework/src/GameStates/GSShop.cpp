#include "GSShop.h"
#include "Camera.h"
GSShop::GSShop() : GameStateBase(StateType::STATE_SHOP),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_text(nullptr)
{
}


GSShop::~GSShop()
{
}

void GSShop::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);
	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ARCADECLASSIC.ttf");
	m_text = std::make_shared< Text>(shader, font, "Find My Grandmaaaaaaaaa", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_text->Set2DPosition(Vector2(60, 200));

	std::string name = "Alarm01.wav";
	ResourceManagers::GetInstance()->PlaySound(name);
}

void GSShop::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSShop::Pause()
{
}

void GSShop::Resume()
{
}


void GSShop::HandleEvents()
{
}

void GSShop::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSShop::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSShop::HandleMouseMoveEvents(int x, int y)
{
}

void GSShop::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSShop::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_text->Draw();
}
