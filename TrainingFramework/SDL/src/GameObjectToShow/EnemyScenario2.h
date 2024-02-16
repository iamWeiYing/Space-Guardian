#include "EnemyScenario1.h"

class EnemyScenario2 : public EnemyScenario
{
public:
	EnemyScenario2(std::shared_ptr<EnemyPool> enemy, float timeBetweenSpawn = 1.0f, int TotalOfSpawn = 5) : EnemyScenario(enemy, timeBetweenSpawn, TotalOfSpawn) {
		mSpawnNumber = 0;
	}
	
	~EnemyScenario2() {
		mEnemyPool = NULL;
		printf("Delete EnenmyScenario2\n");
	}

	void Update(float deltaTime) {
		mCurrentTime += deltaTime;
		if (mSpawnNumber < mTotalOfSpawn) {
			if (mCurrentTime > mTimeBetweenSpawn) {
				mSpawnNumber++;
				mEnemyPool->SetSpawn(rand() % 9);
				mCurrentTime = 0;
			}
			return;
		}

		IsDead = true;
	}
};
