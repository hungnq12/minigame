#include "GSWin.h"
#include "Camera.h"

GSWin::GSWin()
{
}

GSWin::~GSWin()
{
}

void GSWin::Init()
{
	// background
	auto model_bg = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_bg = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_bg = ResourceManagers::GetInstance()->GetTexture("Previewx3.tga");
	m_background = std::make_shared<Sprite2D>(model_bg, shader_bg, texture_bg);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button exit
	auto model_b = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader_b = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture_b3 = ResourceManagers::GetInstance()->GetTexture("btn-mainmenu.tga");
	std::shared_ptr<GameButton> button3 = std::make_shared<GameButton>(model_b, shader_b, texture_b3);
	button3->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button3->SetSize(200, 75);
	button3->SetOnClick([this]() {
		ResourceManagers::GetInstance()->Mute();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button3);

	//// button next
	//auto texture_b4 = ResourceManagers::GetInstance()->GetTexture("btn-mainmenu.tga");
	//std::shared_ptr<GameButton> button4 = std::make_shared<GameButton>(model_b, shader_b, texture_b4);
	//button4->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 100);
	//button4->SetSize(200, 75);
	//button4->SetOnClick([this]() {
	//	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
	//	});
	//m_listButton.push_back(button4);

	// game title
	auto shader_t = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("BreatheFireIii-PKLOB.ttf");
	m_textGameName = std::make_shared< Text>(shader_t, font, "You Win", TextColor::RED, 3.0);
	m_textGameName->Set2DPosition(300, 200);

}
void GSWin::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSWin::Pause()
{
}

void GSWin::Resume()
{
}


void GSWin::HandleEvents()
{
}

void GSWin::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSWin::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSWin::HandleMouseMoveEvents(int x, int y)
{
}

void GSWin::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSWin::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}
