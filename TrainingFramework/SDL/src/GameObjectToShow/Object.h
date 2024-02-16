#pragma once
#include "SpriteAnimation.h"
#include <vector>
#include <functional>

class Object : virtual public BaseObject {
protected:
	float m_Velocity = 100.0f;
	
public:
	static inline std::function<void(void)> onPlayerPointUpdate;
	std::shared_ptr<SpriteAnimation> CurrentAnimation;
	Vector2 MoveDirection;
	SDL_Rect Collider;
	bool IsActive = false;
	const char* Tag;

	Object() {

	}
	void Init() override {
	}

	~Object() {
	}

	virtual void Move(float deltaTime) {};
	void Update(float deltatime) override {
		Collider.x = static_cast<int>(m_position.x);
		Collider.y = static_cast<int>(m_position.y);
		Collider.w = CurrentAnimation->GetWidth();
		Collider.h = CurrentAnimation->GetHeight();
	}

	void SetVelocity(float velocity) {
		m_Velocity = velocity;
	}
};
