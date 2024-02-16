#include "GSPause.h"

GSPause::GSPause() : GameStateBase(StateType::STATE_PAUSE), m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textPause(nullptr), m_Sound(nullptr)
{
}


GSPause::~GSPause()
{
}



void GSPause::Init()
{
	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_main.png");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//Text
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_frame = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_frame->SetSize(300, 100);
	m_frame->Set2DPosition((SCREEN_WIDTH - m_frame->GetWidth()) / 2, 80);

	SDL_Color m_textColor = { 255,255,255 };
	m_textPause = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textPause->SetSize(250, 100);
	m_textPause->Set2DPosition((SCREEN_WIDTH - m_textPause->GetWidth()) / 2, 80);
	m_textPause->LoadFromRenderText("PAUSE");

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 - 80);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(150, 150);
	btnClose->Set2DPosition((SCREEN_WIDTH - btnClose->GetWidth()) / 2, (SCREEN_HEIDHT - btnClose->GetHeight()) / 2 + 80);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);
	

	//game music
	m_Sound = std::make_shared<Sound>("Data/Sounds/Music_Play.mp3");
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
		m_Sound->Volume(MIX_MAX_VOLUME);
	}
	else {
		m_Sound->PauseSound();
	}
}

void GSPause::Exit()
{

}


void GSPause::Pause()
{

}

void GSPause::Resume()
{

}


void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(SDL_Event& e)
{
}

void GSPause::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(int x, int y)
{
}
void GSPause::Update(float deltaTime)
{
	
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_frame->Draw(renderer);
	m_textPause->Draw(renderer);
}
