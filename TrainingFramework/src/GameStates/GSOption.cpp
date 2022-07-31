#include "GSOption.h"
#include "Camera.h"

GSOption::GSOption()
{
}

GSOption::~GSOption()
{
}

void GSOption::Init()
{
	// background
	auto model_bg = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_bg = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_bg = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
	m_background = std::make_shared<Sprite2D>(model_bg, shader_bg, texture_bg);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button back
	auto model_b = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_b = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_b2 = ResourceManagers::GetInstance()->GetTexture("btn-back.tga");
	std::shared_ptr<GameButton> button2 = std::make_shared<GameButton>(model_b, shader_b, texture_b2);
	button2->Set2DPosition(Globals::screenWidth - 100, 50);
	button2->SetSize(100, 40);
	button2->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button2);

	// button exit
	auto texture_b3 = ResourceManagers::GetInstance()->GetTexture("btn-mainmenu.tga");
	std::shared_ptr<GameButton> button3 = std::make_shared<GameButton>(model_b, shader_b, texture_b3);
	button3->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button3->SetSize(200, 75);
	button3->SetOnClick([this]() {
		ResourceManagers::GetInstance()->Mute();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button3);

	// button volumn
	auto texture_b4 = ResourceManagers::GetInstance()->GetTexture("btn-volumn.tga");
	std::shared_ptr<GameButton> button4 = std::make_shared<GameButton>(model_b, shader_b, texture_b4);
	button4->Set2DPosition(Globals::screenWidth / 2-50, Globals::screenHeight / 2 + 100);
	button4->SetSize(200, 75);
	button4->SetOnClick([this]() {
		});
	m_listButton.push_back(button4);

	auto texture_bu = ResourceManagers::GetInstance()->GetTexture("down.tga");
	std::shared_ptr<GameButton> button5 = std::make_shared<GameButton>(model_b, shader_b, texture_bu);
	button5->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 + 100);
	button5->SetSize(75, 75);
	button5->SetOnClick([this]() {
		Globals::volumn += 2.0f;
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		});
	m_listButton.push_back(button5);

	auto texture_bd = ResourceManagers::GetInstance()->GetTexture("up.tga");
	std::shared_ptr<GameButton> button6 = std::make_shared<GameButton>(model_b, shader_b, texture_bd);
	button6->Set2DPosition(Globals::screenWidth / 2 + 200, Globals::screenHeight / 2 + 100);
	button6->SetSize(75, 75);
	button6->SetOnClick([this]() {
		Globals::volumn -= 1.0f;
		if (Globals::volumn <= 0) Globals::volumn = 0;
		ResourceManagers::GetInstance()->PlaySound("MI_SFX 38.wav", false, Globals::volumn);
		});
	m_listButton.push_back(button6);

	// game title
	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("BreatheFireIii-PKLOB.ttf");
	m_textGameName = std::make_shared< Text>(shader_t, font, "Credit @ NQHung", TextColor::RED, 3.0);
	m_textGameName->Set2DPosition(200, 200);
}
void GSOption::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSOption::Pause()
{
}

void GSOption::Resume()
{
}


void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSOption::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}
