#include "SoundManager.h"

void SoundManager::Init()
{
	sfx = std::make_shared<Sfx>("Data/Sounds/Eff_explosion.wav");
	sfx->Volume(50);
	sfxs.insert(std::pair<std::string,std::shared_ptr<Sfx>>("TakeDamage", sfx));

	sfx = std::make_shared<Sfx>("Data/Sounds/Eff_shot.wav");
	sfx->Volume(10);
	sfxs.insert(std::pair<std::string, std::shared_ptr<Sfx>>("Shoot", sfx));

	sfx = std::make_shared<Sfx>("Data/Sounds/Eff_buff.wav");
	sfxs.insert(std::pair<std::string, std::shared_ptr<Sfx>>("PowerUp", sfx));

	sfx = std::make_shared<Sfx>("Data/Sounds/Eff_enemydead.wav");
	sfxs.insert(std::pair<std::string, std::shared_ptr<Sfx>>("Dead", sfx));
}

void SoundManager::PlaySound(std::string key)
{
	if (sfxs.count(key) == 1) {
		if (sfxs[key]->isPlaying) {
			sfxs[key]->PlaySfx();
		}
	}
}
