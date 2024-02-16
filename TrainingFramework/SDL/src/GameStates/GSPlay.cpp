
#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
//#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "GameObjectToShow/CollisionDetection.h"
#include "Text.h"




GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
	printf("Delete GSPlay\n");
}


void GSPlay::Init()
{
	enemyPool = std::make_shared<EnemyPool>();
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	


	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_play.png");
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	/*texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);*/

	//button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		});
	m_listButton.push_back(button);

   //Player
	player = std::make_shared<Player>();
	player->Init();
	enemyPool->Init();

	//game music
	m_Sound = std::make_shared<Sound>("Data/Sounds/Music_Play.mp3");
	m_Sound->Volume(20);
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
	}
	else {
		m_Sound->PauseSound();
	}

	//health bar
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_healthBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_healthBar->SetSize(150, 50);
	m_healthBar->Set2DPosition(10, 10);

	texture = ResourceManagers::GetInstance()->GetTexture("Health.png");
	m_health = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_health->SetSize(player->HealthCheck() * 4, 27);
	m_health->Set2DPosition(25, 20);

	//Player Point
	texture = ResourceManagers::GetInstance()->GetTexture("Credit.tga");
	m_scoreBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_scoreBar->SetSize(200, 50);
	m_scoreBar->Set2DPosition(165, 10);

	SDL_Color m_textColor = { 255,255,255 };
	m_textLine = std::make_shared<Text>("Data/CreditFont.ttf", m_textColor);
	m_textLine->SetSize(25, 50);
	m_textLine->Set2DPosition((350 - m_textLine->GetWidth()), 10);
	m_textLine->LoadFromRenderText("0");

	player->onPlayerPointUpdate = [=]() mutable {
		player->Point += 1;
		m_textLine->SetSize(25 * (std::to_string(player->Point).length()), 50);
		m_textLine->Set2DPosition((350 - m_textLine->GetWidth()), 10);
		m_textLine->LoadFromRenderText(std::to_string(player->Point));
	};

	//HighScoreFile
	std::ifstream MyFile("Data/HighScore.txt");
	std::string text;
	while (std::getline(MyFile, text)) {
		Highscore = stoi(text);
	}
	MyFile.close();
}


void GSPlay::Exit()
{
	if (Highscore < player->Point)
	{
		Highscore = player->Point;
	}
	std::ofstream MyFile("Data/HighScore.txt");
	MyFile << std::to_string(Highscore);
	MyFile.close();

	CollisionDetection::GetInstance()->FreeInstance();
}


void GSPlay::Pause()
{
	m_Sound->PauseSound();
}


void GSPlay::Resume()
{
	m_Sound->Volume(60);
	if (m_Sound->isPlaying) {
		m_Sound->ResumeSound();
	}
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	player->HandleKeyEvent(e);
	
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}


float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void GSPlay::PlayScenario(float deltaTime) {
	currentTime += deltaTime;
	float currentTimeDelay = 7.0f - currentDifficulty ;
	if (currentTime >= currentTimeDelay) {
		if (RandomFloat(0.0f, 100.0f) > 30.0f) {
			enemyScenario = std::make_shared<EnemyScenario1>(enemyPool, 1.0f, 5 + currentDifficulty);
			m_listScenario.push_back(enemyScenario);
		}
		else {
			enemyScenario = std::make_shared<EnemyScenario2>(enemyPool, 1.0f, 5 + currentDifficulty);
			m_listScenario.push_back(enemyScenario);
		}
		spawnAmount++;
		if (spawnAmount >= 5) {
			spawnAmount = 0;
			enemyPool->Health += 1;
			currentDifficulty++;
			if (currentDifficulty >= 4) {
				currentDifficulty = 4;
			}
		}
		currentTime = 0;
	}
}


void GSPlay::Update(float deltaTime)
{
	player->Update(deltaTime);
	if (!player->IsActive)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_ENDING);
	}

	PlayScenario(deltaTime);

	for (int i = 0;i < m_listScenario.size(); i++) {
		m_listScenario[i]->Update(deltaTime);
	}

	for (std::vector<std::shared_ptr<EnemyScenario>>::iterator it = m_listScenario.begin(); it != m_listScenario.end(); ) {
		if (it->get()->IsDead) {
			it = m_listScenario.erase(it);
		}
		else {
			it++;
		}
	}

	enemyPool->Update(deltaTime);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	scrolling_offset++;
	if (scrolling_offset > m_background->GetHeight()) {
		scrolling_offset = 0;
	}

	//m_health->Update(deltaTime);
	m_health->SetSize(player->HealthCheck() * 4, 27);
	


	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Set2DPosition(0, scrolling_offset);
	m_background->Draw(renderer);
	m_background->Set2DPosition(0, scrolling_offset - m_background->GetHeight());
	m_background->Draw(renderer);

	player->Draw(renderer);
	enemyPool->Draw(renderer);

	m_healthBar->Draw(renderer);
	m_health->Draw(renderer);
	m_scoreBar->Draw(renderer);
	m_textLine->Draw(renderer);

	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}