#pragma once

#include "Object.h"

class Bullet: public Object
{
public:
	bool IsEnemy = false;
	Vector2 MoveDirection = Vector2(0, 1);
	Bullet(const char* textureName, Vector2 size, int frameCount);
	~Bullet();
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void SetSpawnPoint(Vector2 spawnPoint);
	void PlaySound();
};

