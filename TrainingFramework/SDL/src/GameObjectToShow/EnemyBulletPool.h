#pragma once
#include "Bullet.h"

class EnemyBulletPool
{
private:
	std::vector<std::shared_ptr<Bullet>> bullets;
public:
	EnemyBulletPool();
	~EnemyBulletPool();
	void Init();
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer);
	void ShootBullet(Vector2 enemyPosition, int enemyType);
};

