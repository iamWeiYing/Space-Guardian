#pragma once
#include "Object.h"
#include "GameObject/Sfx.h"

enum class POWERUP : int
{
	Shield,
	Damage,
	Heal
};

class PowerUp : public virtual Object
{
private:
public:
	POWERUP Power;
	void ChangePlayerAttribute();
	PowerUp();
	~PowerUp();
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void SetSpawnPoint(Vector2 spawnPoint,int power);
};

