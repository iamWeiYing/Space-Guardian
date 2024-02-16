#include "EnemyBulletPool.h"

EnemyBulletPool::EnemyBulletPool()
{
	for (int i = 0;i < 100;i++) {
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>("Projectile_Enemy.png", Vector2(30, 30), 3);
		bullet->MoveDirection = Vector2(0, -1);
		bullet->Tag = "EnemyBullet";
		bullet->IsEnemy = true;
		bullets.push_back(bullet);
	}
}

EnemyBulletPool::~EnemyBulletPool()
{
	printf("Delete EnemyBulletPool\n");
}

void EnemyBulletPool::Init()
{
}

void EnemyBulletPool::Update(float deltaTime)
{
	for (auto bullet : bullets) {
		bullet->Update(deltaTime);

		if (bullet->IsActive) {
			if (bullet->GetPosition().x < 0 || bullet->GetPosition().x>480) {
				bullet->IsActive = false;
			}
			else if (bullet->GetPosition().y < 0 || bullet->GetPosition().y>800) {
				bullet->IsActive = false;
			}
		}
	}
}

void EnemyBulletPool::Draw(SDL_Renderer* renderer)
{
	for (auto bullet : bullets) {
		bullet->Draw(renderer);
	}
}

void EnemyBulletPool::ShootBullet(Vector2 enemyPosition, int enemyType)
{
	int bulletCount = 0;
	float angle = 0.0f;

	for (auto bullet : bullets) {
		if (!bullet->IsActive) {
			bullet->CurrentAnimation->SetRotation(0);
			if (enemyType == 0) {
				bullet->IsActive = true;
				bullet->SetSpawnPoint(enemyPosition);
				bullet->MoveDirection = Vector2(0, -1);
				bullet->PlaySound();
				return;
			}
			else {
				if (bulletCount > 1 + (enemyType - 1)) {
					return;
				}
				else {
					bullet->IsActive = true;

					float projectileDirXPosition;
					float projectileDirYPosition;
					Vector2 spawnPosition = enemyPosition;

					if (enemyType % 2 != 0 && bulletCount % 2 == 0) {
						angle += 15;
					}

					if (bulletCount % 2 == 0) {
						projectileDirXPosition = spawnPosition.x + sin((angle * M_PI) / 180);
						projectileDirYPosition = spawnPosition.y + cos((angle * M_PI) / 180);
						bullet->CurrentAnimation->SetRotation(-angle);
					}
					else {
						projectileDirXPosition = spawnPosition.x + sin(((-angle) * M_PI) / 180);
						projectileDirYPosition = spawnPosition.y + cos(((-angle) * M_PI) / 180);
						bullet->CurrentAnimation->SetRotation(angle);
					}

					Vector2 projectileVector = Vector2(projectileDirXPosition, projectileDirYPosition);
					Vector2 projectileMoveDirection = (spawnPosition - projectileVector).Normalize();

					bullet->SetSpawnPoint(spawnPosition);
					bullet->MoveDirection = projectileMoveDirection;

					if (enemyType % 2 == 0 && bulletCount % 2 == 0) {
						angle += 15;
					}

					bulletCount++;
				}
			}
		}
	}

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>("Projectile_Enemy.png", Vector2(30, 30), 3);
	bullet->MoveDirection = Vector2(0, -1);
	bullet->IsActive = true;
	bullet->IsEnemy = true;
	if (enemyType == 0) {
		bullet->IsActive = true;
		bullet->SetSpawnPoint(enemyPosition);
		bullet->PlaySound();
		return;
	}
	else {
		if (bulletCount > 1 + (enemyType - 1)) {
			return;
		}
		else {
			bullet->IsActive = true;

			float projectileDirXPosition;
			float projectileDirYPosition;
			Vector2 spawnPosition = enemyPosition;

			if (enemyType % 2 != 0 && bulletCount % 2 == 0) {
				angle += 15;
			}

			if (bulletCount % 2 == 0) {
				projectileDirXPosition = spawnPosition.x + sin((angle * M_PI) / 180);
				projectileDirYPosition = spawnPosition.y + cos((angle * M_PI) / 180);
				bullet->CurrentAnimation->SetRotation(-angle);
			}
			else {
				projectileDirXPosition = spawnPosition.x + sin(((-angle) * M_PI) / 180);
				projectileDirYPosition = spawnPosition.y + cos(((-angle) * M_PI) / 180);
				bullet->CurrentAnimation->SetRotation(angle);
			}

			Vector2 projectileVector = Vector2(projectileDirXPosition, projectileDirYPosition);
			Vector2 projectileMoveDirection = (spawnPosition - projectileVector).Normalize();

			bullet->SetSpawnPoint(spawnPosition);
			bullet->MoveDirection = projectileMoveDirection;

			if (enemyType % 2 == 0 && bulletCount % 2 == 0) {
				angle += 15;
			}

			bulletCount++;
		}
	}
	bullet->Tag = "EnemyBullet";
	bullets.push_back(bullet);
}
