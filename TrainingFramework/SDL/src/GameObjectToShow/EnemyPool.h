#pragma once
#include <vector>
#include "Enemy.h"

class EnemyPool
{
private:
	std::shared_ptr<EnemyBulletPool> enemiesBulletPools;
	std::shared_ptr<PowerUpPool> powerUp;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<Enemy> enemy;

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
public:
	int Health = 3;
	EnemyPool();
	~EnemyPool();
	void Update(float deltaTime);
	void Init();
	void Draw(SDL_Renderer* renderer);
	void SetSpawn(int path);
};

