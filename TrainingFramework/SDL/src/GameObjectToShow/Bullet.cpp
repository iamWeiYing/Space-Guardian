#include "Bullet.h"
#include "ResourceManagers.h"
#include "CollisionDetection.h"
#include "SoundManager.h"

Bullet::Bullet(const char* textureName,Vector2 size, int frameCount) {
	Object::Init();
	auto texture = ResourceManagers::GetInstance()->GetTexture(textureName);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
	CurrentAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	CurrentAnimation->SetSize(size.x, size.y);

	CollisionDetection::GetInstance()->Objects.push_back(this);
}

Bullet::~Bullet() {
	if (IsEnemy) {
		printf("Delete Enemy Bullet\n");
	}
	else {
		printf("Delete Player Bullet\n");
	}
}

void Bullet::Update(float deltatime) {
	if (!IsActive) {
		return;
	}
	Object::Update(deltatime);
	Move(deltatime);
}

void Bullet::Move(float deltaTime) {
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x - MoveDirection.x * deltaTime * m_Velocity, m_position.y - MoveDirection.y * deltaTime * m_Velocity);
	CurrentAnimation->Update(deltaTime);
}

void Bullet::Init() {
}

void Bullet::Draw(SDL_Renderer* renderer) {
	if (!IsActive) {
		return;
	}
	CurrentAnimation->Draw(renderer);
}

void Bullet::SetSpawnPoint(Vector2 spawnPoint) {
	CurrentAnimation->Set2DPosition(spawnPoint.x, spawnPoint.y);
}

void Bullet::PlaySound()
{
	SoundManager::GetInstance()->PlaySound("Shoot");
}
