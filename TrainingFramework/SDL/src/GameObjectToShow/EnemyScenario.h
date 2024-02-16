#include "EnemyPool.h"

class EnemyScenario {
protected:
	int mSpawnNumber = 0;
	int mTotalOfSpawn = 5;
	float mCurrentTime = 0.0f;
	float mTimeBetweenSpawn = 1.0f;
	std::shared_ptr<EnemyPool> mEnemyPool;
public:
	bool IsDead = false;

	EnemyScenario(std::shared_ptr<EnemyPool> enemy, float timeBetweenSpawn = 1.0f, int TotalOfSpawn = 5) {
		mEnemyPool = enemy;
		mTotalOfSpawn = TotalOfSpawn;
		mTimeBetweenSpawn = timeBetweenSpawn;
	}
	
	~EnemyScenario() {

	}

	virtual void Update(float deltaTime) = 0;
};
