#include "Player.h"
#include "Define.h"
#include "GameManager/ResourceManagers.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "CollisionDetection.h"
#include "SoundManager.h"
#include <math.h>

//std::vector<std::shared_ptr<SpriteAnimation>> Player::list_animation;

Player::Player() {
	Object::Init();
	text = "Player" + std::to_string(skinID) + "_Idle.png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	CurrentAnimation->SetSize(32, 45);
	CurrentAnimation->Set2DPosition(240, 550);
	list_animation.push_back(CurrentAnimation);

	text = "Player" + std::to_string(skinID) + "_Left.png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	CurrentAnimation->SetSize(32, 45);
	CurrentAnimation->Set2DPosition(240, 550);
	list_animation.push_back(CurrentAnimation);

	text = "Player" + std::to_string(skinID) + "_Right.png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	CurrentAnimation->SetSize(32, 45);
	CurrentAnimation->Set2DPosition(240, 550);
	list_animation.push_back(CurrentAnimation);

	CurrentAnimation = list_animation[0];
	m_position = CurrentAnimation->GetPosition();

	texture = ResourceManagers::GetInstance()->GetTexture("Shield.png");
	shield_animation = std::make_shared<SpriteAnimation>(texture, 1, 10, 1, 0.2f);
	shield_animation->SetSize(45, 45);

	spawnPosition = Vector2(m_position.x, m_position.y - 20);

	for (int i = 0;i < 100;i++) {
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>("Projectile_Player.png", Vector2(16, 30), 4);
		bullet->SetSpawnPoint(spawnPosition);
		bullet->Tag = "PlayerBullet";
		bullet->SetVelocity(600.0f);
		bullets.push_back(bullet);
	}

	IsActive = true;
	Tag = "Player";
	m_instance = this;
	m_Velocity = 125.0f;

	CollisionDetection::GetInstance()->Objects.push_back(this);
}

Player::~Player() {
	Object::~Object();
	printf("Delete Player\n");
}

void Player::HandleEvent(SDL_Event &e) {

}

void Player::HandleKeyEvent(SDL_Event& e) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		if (e.key.keysym.sym == SDLK_UP) {
			m_KeyPress |= 1 << 3;
		}
		else if (e.key.keysym.sym == SDLK_DOWN) {
			m_KeyPress |= 1 << 1;
		}

		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_KeyPress |= 1 << 2;
		}
		else if (e.key.keysym.sym == SDLK_LEFT) {
			m_KeyPress |= 1;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}

	if (m_KeyPress & 1) {
		CurrentAnimation = list_animation[1];
		MoveDirection.x = -1;
	}
	else if (m_KeyPress & 4) {
		CurrentAnimation = list_animation[2];
		MoveDirection.x = 1;
	}
	else {
		MoveDirection.x = 0;
		CurrentAnimation = list_animation[0];
	}
	if (m_KeyPress & 2) {
		MoveDirection.y = 1;
	}
	else if (m_KeyPress & 8) {
		MoveDirection.y = -1;
	}
	else {
		MoveDirection.y = 0;
	}
}

void Player::Init() {

}

void Player::Update(float deltatime) {

	Collider.x = static_cast<int>(m_position.x) + 10;
	Collider.y = static_cast<int>(m_position.y) + 5;
	Collider.w = CurrentAnimation->GetWidth() - 20;
	Collider.h = CurrentAnimation->GetHeight() - 20;

	if (!IsActive) {
		return;
	}

	Move(deltatime);
	spawnPosition = Vector2(m_position.x + 5, m_position.y - 20);

	currentShootTimer += deltatime;
	if (currentShootTimer >= shootTime) {
		Shoot();
		currentShootTimer = 0.0f;
	}

	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Update(deltatime);
			if (bullet->GetPosition().y < 0) {
				bullet->IsActive = false;
			}
		}
	}
	
	for (auto anim : list_animation) {
		anim->Update(deltatime);
	}

	if (CurrentShieldTimer > 0) {
		CurrentShieldTimer -= deltatime;
		shield_animation->Set2DPosition(m_position.x - 5, m_position.y);
		shield_animation->Update(deltatime);

		return;
	}

	for (auto obj : CollisionDetection::GetInstance()->Objects) {
		if (obj->IsActive) {
			if (obj->Tag == "EnemyBullet") {
				if (CollisionDetection::GetInstance()->AABB(this->Collider, obj->Collider)) {
					obj->IsActive = false;
					TakeDamage(1);
				}
			}
			else if (obj->Tag == "Enemy") {
				if (CollisionDetection::GetInstance()->AABB(this->Collider, obj->Collider)) {
					obj->IsActive = false;
					TakeDamage(5);
				}
			}
		}
	}
}

void Player::Draw(SDL_Renderer* renderer) {
	if (!IsActive) {
		return;
	}

	for (auto bullet : bullets) {
		if (bullet->IsActive) {
			bullet->Draw(renderer);
		}
	}

	CurrentAnimation->Draw(renderer);

	if (CurrentShieldTimer > 0) {
		shield_animation->Draw(renderer);
	}
}

void Player::Move(float deltaTime) {
	for (auto anim : list_animation) {
		m_position = anim->GetPosition();
		Vector2 addPosition = Vector2(MoveDirection.x * deltaTime * m_Velocity, MoveDirection.y * deltaTime * m_Velocity);
		anim->Set2DPosition(std::clamp(m_position.x + addPosition.x, 0.0f, (float)SCREEN_WIDTH - 40), std::clamp(m_position.y + addPosition.y, 0.0f, (float)SCREEN_HEIDHT - 60));
	}
}

void Player::Shoot() {
	float angleStep;
	if (NumberOfProjectile < 4) {
		angleStep = (15.0f + 15.0f * (NumberOfProjectile - 1)) / NumberOfProjectile;
	}
	else {
		angleStep = 60.0f / NumberOfProjectile;
	}
	float angle = 0.0f;
	int bulletCount = 0;

	for (auto bullet : bullets) {
		if (!bullet->IsActive) {
			bullet->PlaySound();

			if (bulletCount < NumberOfProjectile) {
				bullet->IsActive = true;

				float projectileDirXPosition;
				float projectileDirYPosition;

				if (bulletCount % 2 == 0 && NumberOfProjectile % 2 == 0) {
					angle += angleStep;
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
				Vector2 projectileMoveDirection = (projectileVector - spawnPosition).Normalize();

				bullet->SetSpawnPoint(spawnPosition);
				bullet->MoveDirection = projectileMoveDirection;

				if (bulletCount % 2 == 0 && NumberOfProjectile % 2 != 0) {
					angle += angleStep;
				}

				bulletCount++;
			}
			else {
				break;
			}
		}
	}
}

void Player::TakeDamage(float damage) {
	currentHealth -= damage;
	SoundManager::GetInstance()->PlaySound("TakeDamage");

	if (currentHealth <= 0) {
		currentHealth = 0;
		Die();
	}
}

void Player::Die() {
	IsActive = false;
}

void Player::Heal() {
	currentHealth = maxHealth;
}

float Player::HealthCheck() {
	return currentHealth;
}