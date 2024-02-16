#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
#include "GameObject/Sfx.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/TextureManager.h"
#include "GameObjectToShow/Option.h"
class GSOption :
	public GameStateBase
{
public:
	GSOption();
	~GSOption();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	SDL_Color	m_textColor;
	std::vector<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<Sound>					m_Sound;
	std::shared_ptr<Sfx>					m_Sfx;
	float time = 0.0f;
};