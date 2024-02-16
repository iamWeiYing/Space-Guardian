#include "PowerUp.h"
#include "Define.h"
#include "CollisionDetection.h"
#include "ResourceManagers.h"
#include "Player.h"
#include "SoundManager.h"

PowerUp::PowerUp()
{
	Object::Init();
	auto texture = ResourceManagers::GetInstance()->GetTexture("Item_Booster.png");
	CurrentAnimation = std::make_shared<SpriteAnimation>(texture, 1, 5, 1, 0.2f);
	CurrentAnimation->SetSize(50,50);

	Tag = "PowerUp";

	CollisionDetection::GetInstance()->Objects.push_back(this);
}

PowerUp::~PowerUp()
{
	printf("Delete PowerUp\n");
}

void PowerUp::Init()
{
}

void PowerUp::Draw(SDL_Renderer* renderer)
{
	if (!IsActive) {
		return;
	}

	CurrentAnimation->Draw(renderer);
}

void PowerUp::Update(float deltatime)
{
	if (!IsActive) {
		return;
	}

	Object::Update(deltatime);
	m_position = CurrentAnimation->GetPosition();
	CurrentAnimation->Set2DPosition(m_position.x, m_position.y + m_Velocity * deltatime);
	CurrentAnimation->Update(deltatime);

	if (m_position.y > SCREEN_HEIDHT) {
		IsActive = false;
	}
	
	for (auto obj : CollisionDetection::GetInstance()->Objects) {
		if (obj->IsActive && obj->Tag == "Player") {
			if (CollisionDetection::GetInstance()->AABB(this->Collider, obj->Collider)) {
				IsActive = false;
				ChangePlayerAttribute();
			}
		}
	}
}

void PowerUp::Move(float deltaTime)
{
}

void PowerUp::SetSpawnPoint(Vector2 spawnPoint,int power)
{
	CurrentAnimation->Set2DPosition(spawnPoint);
	m_position = CurrentAnimation->GetPosition();
	Power = static_cast<POWERUP>(power);
	

	std::shared_ptr<TextureManager> texture;

	switch (Power)
	{
	case POWERUP::Shield:
		texture = ResourceManagers::GetInstance()->GetTexture("Item_S.png");
		CurrentAnimation->SetTexture(texture);
		break;
	case POWERUP::Damage:
		texture = ResourceManagers::GetInstance()->GetTexture("Item_C.png");
		CurrentAnimation->SetTexture(texture);
		break;
	case POWERUP::Heal:
		texture = ResourceManagers::GetInstance()->GetTexture("Item_H.png");
		CurrentAnimation->SetTexture(texture);
		break;
	default:
		break;
	}
	
}

void PowerUp::ChangePlayerAttribute()
{
	switch (Power)
	{
	case POWERUP::Shield:
		Player::GetPlayer()->CurrentShieldTimer += 5;
		break;
	case POWERUP::Damage:
		Player::GetPlayer()->NumberOfProjectile += 1;
		break;
	case POWERUP::Heal:
		Player::GetPlayer()->Heal();
		break;
	default:
		break;
	}

	SoundManager::GetInstance()->PlaySound("PowerUp");
}
