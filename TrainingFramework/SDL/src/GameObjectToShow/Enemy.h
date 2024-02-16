#include "Object.h"
#include "HealthComponent.h"
#include "Define.h"
#include "EnemyBulletPool.h"
#include "PowerUpPool.h"
#include <vector>

class Enemy : public Object, virtual public Health
{
private:
	//Testing

	static std::vector<std::vector<Vector2>> sPaths;

	enum class STATES
	{
		flyIn,
		formation,
		dive,
		dead
	};

	STATES mCurrentStates;
	int mCurrentPath;
	int mCurrentWayPoint;
	const float EPSILON = 5.0f;
	int mEnemyType = 0;

	//Working
	static const inline float CENTER_X = SCREEN_WIDTH / 2;
	static const inline float CENTER_Y = SCREEN_HEIDHT / 2;
	float angle;
	float radius;
	float currentTime = 0.0f;
	Vector2 bulletSpawnPoint;
	float shootTime = 1.0f;
	float currentShootTimer = 0.0f;
	std::vector<std::shared_ptr<SpriteAnimation>> m_listAnimation;

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
public:
	std::shared_ptr<EnemyBulletPool> enemyBulletPool;
	//Testing
	std::shared_ptr<PowerUpPool> PowerUpPools;
	static void CreatePath();

	Enemy(int path);
	~Enemy();
	virtual void HandleFlyInState(float deltaTime);
	virtual void HandleFormationState(float deltaTime);

	void HandleStates(float deltaTime);
	void Reset();

	//Working

	void TakeDamage(float damage) override;
	void Die() override;
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	virtual void Update(float deltatime) override;
	void Move(float deltaTime) override;
	void ShootBullet();
	void ChangePath(int path);
	void ChangeHealth(int health);
	void ChangeEnemy(int enemyType);
};


