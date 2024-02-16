#include "GSCredit.h"
#include "GameObject/TextureManager.h"
#include "GameObject/SpriteAnimation.h"

GSCredit::GSCredit() : GameStateBase(StateType::STATE_CREDIT),
m_background(nullptr), m_creditframe(nullptr), m_howtoplay(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textLine(nullptr)
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	// background
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_main.png");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// game credit
	///Set Font
	m_textColor = { 225, 225, 225 };

	m_textLine = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine->SetSize(200, 50);
	m_textLine->Set2DPosition((SCREEN_WIDTH - m_textLine->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 250 );
	m_textLine->LoadFromRenderText("Thành viên");
	m_listText.push_back(m_textLine);

	m_textLine = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine->SetSize(120, 40);
	m_textLine->Set2DPosition((SCREEN_WIDTH - m_textLine->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 190);
	m_textLine->LoadFromRenderText("Duy Anh");
	m_listText.push_back(m_textLine);

	m_textLine = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine->SetSize(80, 40);
	m_textLine->Set2DPosition((SCREEN_WIDTH - m_textLine->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 150);
	m_textLine->LoadFromRenderText("Quân");
	m_listText.push_back(m_textLine);

	m_Sound = std::make_shared<Sound>("Data/Sounds/Music_Play.mp3");
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
	}
	else {
		m_Sound->PauseSound();
	}

	//Frame
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_creditframe = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_creditframe->SetSize(350, 200);
	m_creditframe->Set2DPosition(SCREEN_WIDTH / 2 - 175, SCREEN_HEIDHT / 2 - 280);

	//how to play
	texture = ResourceManagers::GetInstance()->GetTexture("howtoplay.tga");
	m_howtoplay = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_howtoplay->SetSize(350, 350);
	m_howtoplay->Set2DPosition(SCREEN_WIDTH / 2 - 175, SCREEN_HEIDHT / 2 - 30);
}

void GSCredit::Exit()
{

}


void GSCredit::Pause()
{

}
void GSCredit::Resume()
{

}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(SDL_Event& e)
{
	
}

void GSCredit::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
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
}

void GSCredit::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_creditframe->Draw(renderer);
	m_howtoplay->Draw(renderer);
	for (auto it : m_listText)
	{
		it->Draw(renderer);
	}
}