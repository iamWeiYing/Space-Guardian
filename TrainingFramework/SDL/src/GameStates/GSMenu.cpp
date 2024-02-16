#include "GSMenu.h"
#include <string>
#include <iostream>
#include <fstream>
#include "SoundManager.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}),
m_textGameName(nullptr), m_textHighScore(nullptr), m_textText(nullptr), m_Sound(nullptr)
{
}


GSMenu::~GSMenu()
{
}

std::string LoadFile() {
	std::ifstream MyFile("Data/HighScore.txt");
	std::string text;
	if (MyFile.fail())
	{
		text = "0";
	}
	else
	{
		while (std::getline(MyFile, text)) {
		}
	}
	MyFile.close();
	return text;
}

void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	SoundManager::GetInstance()->Init();
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_main.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	
	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 + 50);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 170);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//CREDIT game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnCredit->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 280);
	btnCredit->SetSize(100, 100);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnCredit);

	// game title
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/TitleFont.ttf", m_textColor);
	m_textGameName->SetSize(350, 50);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 300);
	m_textGameName->LoadFromRenderText("Space Guardian");

	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_frameGameName = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_frameGameName->SetSize(400, 100);
	m_frameGameName->Set2DPosition(SCREEN_WIDTH / 2 - 200, SCREEN_HEIDHT / 2 - 320);

	//Game music
	m_Sound = std::make_shared<Sound>("Data/Sounds/Music_Play.mp3");
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
	}
	else {
		m_Sound->PauseSound();
	}

	//High Score
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_frameHighScore = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_frameHighScore->SetSize(200, 100);
	m_frameHighScore->Set2DPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIDHT / 2 - 180);

	m_textColor = { 255, 255, 0 };
	m_textText = std::make_shared<Text>("Data/TitleFont.ttf", m_textColor);
	m_textText->SetSize(160, 40);
	m_textText->Set2DPosition((SCREEN_WIDTH - m_textText->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 175);
	m_textText->LoadFromRenderText("Highscore");

	std::string text = LoadFile();

	m_textColor = { 255, 255, 0 };
	m_textHighScore = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textHighScore->SetSize(20 * text.length(), 40);
	m_textHighScore->Set2DPosition((SCREEN_WIDTH - m_textHighScore->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 133);
	m_textHighScore->LoadFromRenderText(text);
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
	SoundManager::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->PauseSound();

}

void GSMenu::Resume()
{
	m_Sound->Volume(128);
	if (m_Sound->isPlaying) {
		m_Sound->ResumeSound();
	}

	std::string text = LoadFile();
	m_textHighScore->SetSize(20 * text.length(), 40);
	m_textHighScore->Set2DPosition((SCREEN_WIDTH - m_textHighScore->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 133);
	m_textHighScore->LoadFromRenderText(text);
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
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
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_frameGameName->Draw(renderer);
	m_textGameName->Draw(renderer);
	m_frameHighScore->Draw(renderer);
	m_textHighScore->Draw(renderer);
	m_textText->Draw(renderer);
}
