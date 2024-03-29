#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sound.h"
#include "GameObject/TextureManager.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Text.h"

class GSCredit: public GameStateBase
{
public:
	GSCredit();
	~GSCredit();

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
	int		m_KeyPress;

private:
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Sprite2D> m_creditframe;
	std::shared_ptr<Sprite2D> m_howtoplay;
	std::list<std::shared_ptr<Text>>		m_listText;
	std::shared_ptr<Text>					m_textLine;
	std::shared_ptr<Sound>					m_Sound;
	SDL_Color	m_textColor;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	float time = 0.0f;
};
