#include "GSEnding.h"
#include "GameObjectToShow/Player.h"
GSEnding::GSEnding() : GameStateBase(StateType::STATE_PAUSE), m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textEnding(nullptr), m_Sound(nullptr)
{
}


GSEnding::~GSEnding()
{
}



void GSEnding::Init()
{
	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_main.png");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//Text
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_frame = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_frame->SetSize(375, 100);
	m_frame->Set2DPosition((SCREEN_WIDTH - m_frame->GetWidth()) / 2, 80);

	SDL_Color m_textColor = { 255,255,255 };
	m_textEnding = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textEnding->SetSize(325, 100);
	m_textEnding->Set2DPosition((SCREEN_WIDTH - m_textEnding->GetWidth()) / 2, 80);
	m_textEnding->LoadFromRenderText("YOU DIE");

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(150, 150);
	btnClose->Set2DPosition((SCREEN_WIDTH - btnClose->GetWidth()) / 2, (SCREEN_HEIDHT - btnClose->GetHeight()) / 2);
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

void GSEnding::Exit()
{

}


void GSEnding::Pause()
{

}

void GSEnding::Resume()
{

}


void GSEnding::HandleEvents()
{
}

void GSEnding::HandleKeyEvents(SDL_Event& e)
{
}

void GSEnding::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSEnding::HandleMouseMoveEvents(int x, int y)
{
}
void GSEnding::Update(float deltaTime)
{

	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSEnding::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_frame->Draw(renderer);
	m_textEnding->Draw(renderer);
}