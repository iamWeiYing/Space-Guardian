#include "GSOption.h"

GSOption::GSOption() : GameStateBase(StateType:: STATE_OPTION),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}

GSOption::~GSOption() 
{
}

void GSOption::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG_main.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	m_Sound = std::make_shared<Sound>("Data/Sounds/Music_Play.mp3");
	if (m_Sound->isPlaying) {
		m_Sound->PlaySound();
	}
	else {
		m_Sound->PauseSound();
	}

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// button mute
	if (m_Sound->isPlaying) {
		texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	}
	else {
		texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
	}
	std::shared_ptr<MouseButton> btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusic->SetSize(100, 100);
	btnMusic->Set2DPosition((SCREEN_WIDTH - btnMusic->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 150);
	btnMusic->SetOnClick([=]() mutable {
		if (m_Sound->isPlaying) {
			m_Sound->PauseSound();
			m_Sound->isPlaying = false;
			texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
			btnMusic->SetTexture(texture);
		}
		else {
			m_Sound->PlaySound();
			m_Sound->isPlaying = true;
			texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
			btnMusic->SetTexture(texture);
		}
		});
	m_listButton.push_back(btnMusic);

	//button sfx
	if (m_Sfx->isPlaying) {
		texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
	}
	else {
		texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga");
	}
	std::shared_ptr<MouseButton> btnSfx = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnSfx->SetSize(100, 100);
	btnSfx->Set2DPosition((SCREEN_WIDTH - btnSfx->GetWidth()) / 2, SCREEN_HEIDHT / 2);
	btnSfx->SetOnClick([=]() mutable {
		if (m_Sfx->isPlaying)
		{
			m_Sfx->isPlaying = false;
			texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga");
			btnSfx->SetTexture(texture);
		}
		else
		{
			m_Sfx->isPlaying = true;
			texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
			btnSfx->SetTexture(texture);
		}
		});
	m_listButton.push_back(btnSfx);

	//button skin select
	texture = ResourceManagers::GetInstance()->GetTexture("Player0_Idle.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(60, 75);
	obj->Set2DPosition(SCREEN_WIDTH / 2 - 30, SCREEN_HEIDHT / 2 + 160);
	m_listAnimation.push_back(obj);

	texture = ResourceManagers::GetInstance()->GetTexture("Player1_Idle.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(60, 75);
	obj->Set2DPosition(SCREEN_WIDTH / 2 - 30, SCREEN_HEIDHT / 2 + 160);
	m_listAnimation.push_back(obj);

	texture = ResourceManagers::GetInstance()->GetTexture("Player2_Idle.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(60, 75);
	obj->Set2DPosition(SCREEN_WIDTH / 2 - 30, SCREEN_HEIDHT / 2 + 160);
	m_listAnimation.push_back(obj);

	obj = m_listAnimation[Option::skinID];

	texture = ResourceManagers::GetInstance()->GetTexture("btn_blank.tga");
	std::shared_ptr<MouseButton> btnSkin = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnSkin->SetSize(100, 100);
	btnSkin->Set2DPosition((SCREEN_WIDTH - btnSkin->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 150);
	btnSkin-> SetOnClick([=](){
		Option::skinID++;
		if (Option::skinID > 2) {
			Option::skinID = 0;
		}
		obj = m_listAnimation[Option::skinID];
		});
	m_listButton.push_back(btnSkin);
}

void GSOption::Exit()
{
}

void GSOption::Pause()
{
	//m_Sound->StopSound();
}

void GSOption::Resume()
{
	//m_Sound->PlaySound();
}

void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(SDL_Event& e)
{
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOption::Update(float deltaTime)
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

void GSOption::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	obj->Draw(renderer);
}