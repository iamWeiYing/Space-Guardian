#include "Enemy.h"
#include "ResourceManagers.h"
#include "BezierPath.h"
#include "CollisionDetection.h"
#include "SoundManager.h"

void Enemy::Init() {
}


void Enemy::Update(float deltatime) {
	if (!IsActive) {
		return;
	}

	Object::Update(deltatime);
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Update(deltatime);

	HandleStates(deltatime);
	currentTime += deltatime;
	if (currentTime > 2.0f) {
		currentTime = 0;
		ShootBullet();
	}

	for (auto obj : CollisionDetection::GetInstance()->Objects) {
		if (obj->Tag == "PlayerBullet" && obj->IsActive) {
			if (CollisionDetection::GetInstance()->AABB(this->Collider, obj->Collider)) {
				obj->IsActive = false;
				TakeDamage(1);
			}
		}
	}
}

void Enemy::Move(float deltaTime) {
	CurrentAnimation->Set2DPosition(m_position.x + MoveDirection.x, m_position.y + MoveDirection.y);
}


void Enemy::Draw(SDL_Renderer* renderer) {
	if (!IsActive) {
		return;
	}

	CurrentAnimation->Draw(renderer);

	/*for (int i = 0;i < sPaths[mCurrentPath].size() - 1;i++) {
		Renderer::GetInstance()->DrawLine(sPaths[mCurrentPath][i].x, sPaths[mCurrentPath][i].y, sPaths[mCurrentPath][i + 1].x, sPaths[mCurrentPath][i + 1].y);
	}*/
}

void Enemy::TakeDamage(float damage) {
	currentHealth -= damage;

	if (currentHealth <= 0) {
		currentHealth = 0;
		Die();
	}
}

void Enemy::Die() {
	if (IsActive) {
		SoundManager::GetInstance()->PlaySound("Dead");
		
		onPlayerPointUpdate();
		if (RandomFloat(0.0f, 100.0f) < 10.0f) {
			PowerUpPools->TakeRandomPowerUp(CurrentAnimation->Get2DPosition());
		}
		IsActive = false;
	}
}

void Enemy::ShootBullet() {
	enemyBulletPool->ShootBullet(CurrentAnimation->Get2DPosition(), mEnemyType);
}

//Testing

std::vector<std::vector<Vector2>> Enemy::sPaths;

void Enemy::CreatePath() {

	if (sPaths.size() > 0) {
		return;
	}

	int screenMidPoint = SCREEN_WIDTH * 0.5f;

	//enemy path0
	BezierPath* path0 = new BezierPath();
	
	path0->AddCurve({ Vector2(screenMidPoint + 50, -10), Vector2(screenMidPoint + 50, -20), Vector2(screenMidPoint + 50, 30), Vector2(screenMidPoint + 50, 20) }, 1);
	path0->AddCurve({ Vector2(screenMidPoint + 50, 20), Vector2(screenMidPoint + 50, 100), Vector2(75, 325), Vector2(75, 425) }, 25);
	path0->AddCurve({ Vector2(75, 425), Vector2(75, 650), Vector2(325, 650), Vector2(325, 425) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path0->Sample(&sPaths[0]);
	delete path0;

	//enemy path1
	BezierPath* path1 = new BezierPath();

	path1->AddCurve({ Vector2(screenMidPoint + 70, -10), Vector2(screenMidPoint + 70, -20), Vector2(screenMidPoint + 70, 30), Vector2(screenMidPoint + 70, 20) }, 1);
	path1->AddCurve({ Vector2(screenMidPoint + 70, 20), Vector2(screenMidPoint + 70, 425), Vector2(40, 20), Vector2(40, 425) }, 25);
	path1->AddCurve({ Vector2(40, 425), Vector2(40, 470), Vector2(110, 470), Vector2(170, 425) }, 25);
	path1->AddCurve({ Vector2(170, 425), Vector2(400, 310), Vector2(480, 425), Vector2(360, 475) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path1->Sample(&sPaths[1]);
	delete path1;

	//enemy path2
	BezierPath* path2 = new BezierPath();

	path2->AddCurve({ Vector2(300, -10), Vector2(300, -20), Vector2(300, 30), Vector2(300, 20) }, 1);
	path2->AddCurve({ Vector2(300, 20), Vector2(300, 120), Vector2(370, 240), Vector2(180, 250) }, 25);
	path2->AddCurve({ Vector2(180, 250), Vector2(-70, 280), Vector2(90, 360), Vector2(320, 360) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path2->Sample(&sPaths[2]);
	delete path2;

	//enemy path3
	BezierPath* path3 = new BezierPath();

	path3->AddCurve({ Vector2(40, -10), Vector2(40, -20), Vector2(40, 110), Vector2(40, 100) }, 1);
	path3->AddCurve({ Vector2(screenMidPoint, 100), Vector2(screenMidPoint, 90), Vector2(screenMidPoint, 210), Vector2(screenMidPoint, 200) }, 25);
	path3->AddCurve({ Vector2(SCREEN_WIDTH - 40, 200), Vector2(SCREEN_WIDTH - 40, 190), Vector2(SCREEN_WIDTH - 40, 310), Vector2(SCREEN_WIDTH - 40, 300) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path3->Sample(&sPaths[3]);
	delete path3;

	//enemy path4
	BezierPath* path4 = new BezierPath();

	path4->AddCurve({ Vector2(-40, 160), Vector2(-40, 160), Vector2(screenMidPoint, 160), Vector2(screenMidPoint, 160) }, 1);
	path4->AddCurve({ Vector2(screenMidPoint, 160), Vector2(screenMidPoint + 120, 160), Vector2(screenMidPoint + 120, 320), Vector2(screenMidPoint, 320) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path4->Sample(&sPaths[4]);
	delete path4;

	//enemy path5
	BezierPath* path5 = new BezierPath();

	path5->AddCurve({ Vector2(380, -10), Vector2(380, -20), Vector2(380, 30), Vector2(380, 20) }, 1);
	path5->AddCurve({ Vector2(380, 20), Vector2(380, 60), Vector2(330, 60), Vector2(330, 100) }, 25);
	path5->AddCurve({ Vector2(330, 100), Vector2(320, 160), Vector2(440, 160), Vector2(440, 270) }, 25);
	path5->AddCurve({ Vector2(440, 270), Vector2(435, 380), Vector2(335, 380), Vector2(330, 270) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path5->Sample(&sPaths[5]);
	delete path5;

	//enemy path6
	BezierPath* path6 = new BezierPath();

	path6->AddCurve({ Vector2(SCREEN_WIDTH - 40, -10), Vector2(SCREEN_WIDTH - 40, -20), Vector2(SCREEN_WIDTH - 40, 110), Vector2(SCREEN_WIDTH - 40, 100) }, 1);
	path6->AddCurve({ Vector2(screenMidPoint, 100), Vector2(screenMidPoint, 90), Vector2(screenMidPoint, 210), Vector2(screenMidPoint, 200) }, 25);
	path6->AddCurve({ Vector2(40, 200), Vector2(40, 190), Vector2(40, 310), Vector2(40, 300) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path6->Sample(&sPaths[6]);
	delete path6;

	//enemy path7
	BezierPath* path7 = new BezierPath();

	path7->AddCurve({ Vector2(SCREEN_WIDTH - 40, -10), Vector2(SCREEN_WIDTH - 40, -20), Vector2(SCREEN_WIDTH - 40, 30), Vector2(SCREEN_WIDTH - 40, 20) }, 1);
	path7->AddCurve({ Vector2(SCREEN_WIDTH - 40, 20), Vector2(SCREEN_WIDTH - 40, 70), Vector2(SCREEN_WIDTH - 40, 80), Vector2(SCREEN_WIDTH - 60, 90) }, 25);
	path7->AddCurve({ Vector2(SCREEN_WIDTH - 60, 90), Vector2(280, 120), Vector2(20, 90), Vector2(20, 160) }, 25);
	path7->AddCurve({ Vector2(20, 160), Vector2(20, 205), Vector2(80, 250), Vector2(420, 250) }, 25);
	path7->AddCurve({ Vector2(420, 250), Vector2(SCREEN_WIDTH - 20, 250), Vector2(SCREEN_WIDTH - 20, 320), Vector2(420, 320) }, 25);
	path7->AddCurve({ Vector2(420, 320), Vector2(375, 340), Vector2(290, 340), Vector2(170, 340) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path7->Sample(&sPaths[7]);
	delete path7;

	//enemy path8
	BezierPath* path8 = new BezierPath();

	path8->AddCurve({ Vector2(SCREEN_WIDTH + 40, 80), Vector2(SCREEN_WIDTH + 40, 80), Vector2(80, 80), Vector2(80, 80) }, 1);
	path8->AddCurve({ Vector2(80, 80), Vector2(0, 80), Vector2(0, 160), Vector2(80, 160) }, 25);
	path8->AddCurve({ Vector2(80, 160), Vector2(80, 160), Vector2(SCREEN_WIDTH - 80, 160), Vector2(SCREEN_WIDTH - 80, 160) }, 25);
	path8->AddCurve({ Vector2(SCREEN_WIDTH - 80, 160), Vector2(SCREEN_WIDTH, 160), Vector2(SCREEN_WIDTH, 240), Vector2(SCREEN_WIDTH - 80, 240) }, 25);
	path8->AddCurve({ Vector2(SCREEN_WIDTH - 80, 240), Vector2(SCREEN_WIDTH - 80, 240), Vector2(80, 240), Vector2(80, 240) }, 25);
	path8->AddCurve({ Vector2(80, 240), Vector2(0, 240), Vector2(0, 320), Vector2(80, 320) }, 25);
	path8->AddCurve({ Vector2(80, 320), Vector2(80, 320), Vector2(screenMidPoint + 50, 320), Vector2(screenMidPoint + 50, 320) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path8->Sample(&sPaths[8]);
	delete path8;

}

Enemy::Enemy(int path) {

	mCurrentPath = path;
	Object::Init();
	auto tex = ResourceManagers::GetInstance()->GetTexture("Enemies_AG.png");

	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, 6, 1, 0.2f);
	CurrentAnimation->SetSize(30, 30);
	CurrentAnimation->Set2DPosition(Vector2(480 * 0.4f, 800 * 0.5f));
	m_listAnimation.push_back(CurrentAnimation);

	tex = ResourceManagers::GetInstance()->GetTexture("Enemies_BY.png");
	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, 4, 1, 0.2f);
	CurrentAnimation->SetSize(30, 30);
	CurrentAnimation->Set2DPosition(Vector2(480 * 0.4f, 800 * 0.5f));
	m_listAnimation.push_back(CurrentAnimation);

	tex = ResourceManagers::GetInstance()->GetTexture("Enemies_CP.png");
	CurrentAnimation = std::make_shared<SpriteAnimation>(tex, 1, 5, 1, 0.2f);
	CurrentAnimation->SetSize(30, 30);
	CurrentAnimation->Set2DPosition(Vector2(480 * 0.4f, 800 * 0.5f));
	m_listAnimation.push_back(CurrentAnimation);

	CurrentAnimation = m_listAnimation[0];

	mCurrentStates = STATES::flyIn;

	mCurrentWayPoint = 0;
	CurrentAnimation->Set2DPosition(sPaths[mCurrentPath][mCurrentWayPoint]);

	m_position = CurrentAnimation->GetPosition();

	maxHealth = 3.0f;
	currentHealth = 3.0f;

	Tag = "Enemy";

	CollisionDetection::GetInstance()->Objects.push_back(this);
}

Enemy::~Enemy()
{
	PowerUpPools = NULL;
	enemyBulletPool = NULL;
	printf("Delete Enemy\n");
}

void Enemy::HandleStates(float deltaTime) {
	switch (mCurrentStates)
	{
	case Enemy::STATES::flyIn:
		HandleFlyInState(deltaTime);
		break;	
	case Enemy::STATES::formation:
		HandleFormationState(deltaTime);
		break;
	default:
		break;
	}
}

void Enemy::HandleFlyInState(float deltaTime) {
	if ((sPaths[mCurrentPath][mCurrentWayPoint] - CurrentAnimation->Get2DPosition()).MagnitudeSqr() < EPSILON) {
		mCurrentWayPoint++;
	}

	if (mCurrentWayPoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWayPoint] - CurrentAnimation->Get2DPosition();

		CurrentAnimation->Set2DPosition(CurrentAnimation->Get2DPosition() + dist.Normalize() * deltaTime * m_Velocity);
	}
	else {
		mCurrentStates = STATES::formation;
		Vector2 currentPosition = CurrentAnimation->Get2DPosition();


		radius = sqrt((currentPosition.x - CENTER_X) * (currentPosition.x - CENTER_X) + (currentPosition.y - CENTER_Y) * (currentPosition.y - CENTER_Y));
		angle = atan2(currentPosition.y - CENTER_Y, currentPosition.x - CENTER_X);
	}
}

void Enemy::HandleFormationState(float deltaTime) {
	angle +=  deltaTime;
	CurrentAnimation->Set2DPosition(CENTER_X + radius * cos(angle), CENTER_Y + radius * sin(angle));
}

void Enemy::Reset() {
	currentHealth = maxHealth;
	mCurrentWayPoint = 0;
	CurrentAnimation->Set2DPosition(sPaths[mCurrentPath][mCurrentWayPoint]);
	mCurrentStates = STATES::flyIn;
}

void Enemy::ChangePath(int path) {
	mCurrentPath = path;
}

void Enemy::ChangeHealth(int health)
{
	maxHealth = health;
}

void Enemy::ChangeEnemy(int enemyType)
{
	CurrentAnimation = m_listAnimation[enemyType];
	mEnemyType = enemyType;
}
