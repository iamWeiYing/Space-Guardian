#include "EnemyScenario.h"

class EnemyScenario1: public EnemyScenario
{
private:
	int randomNumber = rand() % 9;
public:
	EnemyScenario1(std::shared_ptr<EnemyPool> enemy, float timeBetweenSpawn = 1.0f, int TotalOfSpawn = 5) : EnemyScenario(enemy, timeBetweenSpawn, TotalOfSpawn) {
		mSpawnNumber = 0;
	}

	~EnemyScenario1() {
		mEnemyPool = NULL;
		printf("Delete EnenmyScenario1\n");
	}

	 void Update(float deltaTime) override {
		mCurrentTime += deltaTime;
		if (mSpawnNumber < mTotalOfSpawn) {
			if (mCurrentTime > mTimeBetweenSpawn) {
				mSpawnNumber++;
				mEnemyPool->SetSpawn(randomNumber);
				mCurrentTime = 0;
			}
			return;
		}

		IsDead = true;
	}
};

