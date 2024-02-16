#include "EnemyPool.h"

EnemyPool::EnemyPool() {
}

EnemyPool::~EnemyPool()
{
	printf("Delete EnemyPool\n");
	//enemies.clear();
}

void EnemyPool::Init() {
	Enemy::CreatePath();
	powerUp = std::make_shared<PowerUpPool>();
	powerUp->Init();

	enemiesBulletPools = std::make_shared<EnemyBulletPool>();
	enemiesBulletPools->Init();

	for (int i = 0;i < 10;i++) {
		enemy = std::make_shared<Enemy>(rand()%9);
		enemy->Init();
		enemy->enemyBulletPool = enemiesBulletPools;
		enemy->PowerUpPools = powerUp;
		enemies.push_back(enemy);
	}
}

void EnemyPool::Update(float deltaTime) {
	powerUp->Update(deltaTime);
	for (auto enemy : enemies) {
		enemy->Update(deltaTime);
	}
	enemiesBulletPools->Update(deltaTime);
}

void EnemyPool::Draw(SDL_Renderer* renderer) {
	powerUp->Draw(renderer);
	for (auto enemy : enemies) {
		enemy->Draw(renderer);
	}
	enemiesBulletPools->Draw(renderer);
}

void EnemyPool::SetSpawn(int path) {
	float rand = RandomFloat(0.0f, 100.0f);
	for (auto enemy : enemies) {
		if (!enemy->IsActive) {
			enemy->IsActive = true;
			enemy->ChangePath(path);
			enemy->ChangeHealth(Health);
			if (rand < 60) {
				enemy->ChangeEnemy(0);
			}
			else if (rand >= 60 && rand < 90) {
				enemy->ChangeEnemy(1);
			}
			else {
				enemy->ChangeEnemy(2);
			}
			enemy->Reset();
			return;
		}
	}

	if (enemies.size() >= 60) {
		return;
	}

	enemy = std::make_shared<Enemy>(path);
	enemy->Init();
	enemy->enemyBulletPool = enemiesBulletPools;
	enemy->PowerUpPools = powerUp;
	enemies.push_back(enemy);
	enemy->IsActive = true;
	enemy->ChangeHealth(Health);
	if (rand < 60) {
		enemy->ChangeEnemy(0);
	}
	else if (rand >= 60 && rand < 90) {
		enemy->ChangeEnemy(1);
	}
	else {
		enemy->ChangeEnemy(2);
	}
	enemy->Reset();
}


		